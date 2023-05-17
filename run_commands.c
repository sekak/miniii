/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:22:57 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:25:08 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_arrays(t_mshel *shel, int index, char *cmd)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	while (shel->cmd[index]->args[i] != NULL)
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 2));
	if (shel->cmd[index]->args == NULL)
	{
		new_cmd[0] = ft_strdup(cmd);
		new_cmd[1] = NULL;
		return (new_cmd);
	}
	i = 0;
	new_cmd[0] = ft_strdup(cmd);
	j = 1;
	while (shel->cmd[index]->args[i] != NULL)
	{
		if (!shel->cmd[index]->args[i] || !shel->cmd[index]->args[i][0])
			i++;
		else if (shel->cmd[index]->args[i])
		{
			new_cmd[j++] = ft_strdup(shel->cmd[index]->args[i]);
			i++;
		}
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

int	run_non_builtin(t_mshel *shel, int cmd_index, char *cmd)
{
	int	status;
	int	exited;

	exited = 0;
	if (shel->cmd_number == 1)
	{
		char **l = join_arrays(shel, cmd_index, cmd);
		if (fork() == 0)
			execute_shell(l, shel);
		else
			wait(&status);
		int i = 0;
		while (l[i])
		{
			free(l[i++]);
		}
		free(l);
		exited = WEXITSTATUS(status);
	}
	else
		execute_shell(join_arrays(shel, cmd_index, cmd), shel);
	return (exited);
}

void	run_cmd(t_mshel *shel, int cmd_index, char *cmd)
{
	int	exited;

	exited = 0;
	if (cmd[0] && (!strncmp(cmd, "echo", strlen("echo")) || \
	!ft_strncmp(cmd, "/bin/echo", ft_strlen("/bin/echo"))))
		ech_o(shel, cmd_index);
	else if (cmd[0] && (!strncmp(cmd, "pwd", strlen("pwd")) || \
	!ft_strncmp(cmd, "/bin/pwd", ft_strlen("/bin/pwd"))))
		p_w_d();
	else if (cmd[0] && (!strncmp(cmd, "cd", strlen("cd")) || \
	!ft_strncmp(cmd, "/usr/bin/cd", ft_strlen("/usr/bin/cd"))))
		exited = c_d(shel, shel->cmd[cmd_index]->args[0]);
	else if (cmd[0] && !strncmp(cmd, "exit", strlen("exit")))
		exited = exit_function(shel->cmd[cmd_index]->args, shel);
	else if (cmd[0] && !ft_strncmp(cmd, "export", strlen("export")))
		exited = ft_export(shel, cmd_index);
	else if (cmd[0] && !strncmp(cmd, "unset", strlen("unset")))
		ft_unset(shel, cmd_index);
	else if (cmd[0] && (!strncmp(cmd, "env", strlen("env")) || \
	!ft_strncmp(cmd, "/usr/bin/env", ft_strlen("/usr/bin/env"))))
		print_env(shel, 0);
	else
		exited = run_non_builtin(shel, cmd_index, cmd);
	shel->exit_status = exited;
}

int	start_redirect_pipe(t_mshel *shel, int cmd_index, int red_status, int status, int (*pipe)[2])
{
	if (!redirect_to_pipe(shel, pipe, cmd_index, red_status, status))
	{
		if (!status && shel->cmd[cmd_index]->redir.heredoc.her_doc == 0)
		{
			if (shel->cmd[cmd_index]->error == -3)
				print_errors("minishell: ambiguous redirect");
			else
				error_to_print(shel->cmd[cmd_index]->error, shel->cmd[cmd_index]->error_file);
			shel->exit_status = 1;
			return(1);
		}
		else if (status)
			exit(1);
	}
	return (0);
}

int	redirect_in_out(t_mshel *shel, int cmd_index,int status)
{
	if (!redirect_input(shel, cmd_index, 0))
	{
		if (shel->cmd[cmd_index]->error == -3)
			print_errors("minishell: ambiguous redirect");
		else
			error_to_print(shel->cmd[cmd_index]->error, shel->cmd[cmd_index]->error_file);
		shel->exit_status = 1;
		if (status)
			exit(1);
		else
			return (1);
	}
	if (!redirect_output(shel, cmd_index))
	{
		if (shel->cmd[cmd_index]->error == -3)
			print_errors("minishell: ambiguous redirect");
		else
			error_to_print(shel->cmd[cmd_index]->error, shel->cmd[cmd_index]->error_file);
		shel->exit_status = 1;
		if (status)
			exit(1);
		else
			return (1);
	}
	return (0);
}

int	reset_redirection(t_mshel *shel, int cmd_index, int status)
{
	if (shel->cmd[cmd_index]->error != -1)
	{
		if (shel->cmd[cmd_index]->error == -3)
			print_errors("minishell: ambiguous redirect");
		else
			error_to_print(shel->cmd[cmd_index]->error, shel->cmd[cmd_index]->error_file);
		shel->exit_status = 1;
		if (status)
			exit(1);
		else
			return(1);
	}
	if (shel->cmd[cmd_index]->redir.old_output != 0)
	{
		if (dup2(shel->cmd[cmd_index]->redir.old_output, STDOUT_FILENO) == -1)
			perror("minishell :");
	}
	if (shel->cmd[cmd_index]->redir.old_input != 0)
	{
		if (dup2(shel->cmd[cmd_index]->redir.old_input, STDIN_FILENO) == -1)
			perror("minishell :");
	}
	return (0);
}

void	execute_cmd(t_mshel *shel, int (*pipe)[2], int cmd_index, int status)
{
	int		red_status;

	red_status = check_redirect_place(shel->cmd[cmd_index]->redir.in, shel->cmd[cmd_index]->redir.out);
	if(start_redirect_pipe(shel, cmd_index, red_status, status, pipe))
		return ;
	if (red_status == 1)
	{
		if(redirect_in_out(shel, cmd_index, status))
			return ;
	}
	if (red_status != 1 && status != 0)
		open_n_close_p(pipe, 1, shel->cmd_number - 1);
	if (shel->cmd[cmd_index]->cmd)
	{
		if (shel->cmd[cmd_index]->redir.heredoc.her_doc == 0)
			run_cmd(shel, cmd_index, shel->cmd[cmd_index]->cmd);
	}
	if (shel->cmd[cmd_index]->redir.heredoc.her_doc > 0)
		ft_heredoc(cmd_index, shel);
	if (shel->cmd_number > 1)
		exit(0);
	if(reset_redirection(shel, cmd_index, status))
		return ;
}
