/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:25:51 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:22:54 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_quotes(char *a, int c)
{
	char *returned;

	if (c == '\'')
		returned = ft_strtrim(a, "'");
	if (c == '"')
		returned = ft_strtrim(a, "\"");
	return (returned);
}

void open_n_close_p(int (*pipes)[2], int cs, int p_number)
{
	int i;

	i = 0;
	if (cs == 0)
	{
		while (i < p_number)
		{
			pipe(pipes[i]);
			i++;
		}
	}
	else
	{
		while (i < p_number)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i++;
		}
	}
}
void printf_in_pipe(char *a, int fd)
{
	int i;

	i = 0;
	if (!a)
	{
		write(fd, "\n", 1);
		return;
	}
	while (a[i])
	{
		write(fd, &a[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void read_line(t_mshel *shel, int cmd_index, int *i, int (*pipes)[2])
{
	char *a;
	char *holder;

	holder = NULL;
	while (1)
	{
		a = readline("heredoc> ");
		if (a == NULL)
		{
			(*i)++;
			break;
		}
		if (ft_strchr(a, '$'))
			holder = check_expanding(shel, a);
		if ((a[0] == '\'' && shel->cmd[cmd_index]->redir.heredoc.delemiter[(*i)][0] == '\'') || (a[0] == '"' && shel->cmd[cmd_index]->redir.heredoc.delemiter[(*i)][0] == '"'))
			holder = remove_quotes(a, a[0]);
		if (!strcmp(a, shel->cmd[cmd_index]->redir.heredoc.delemiter[(*i)]) || (holder && !strcmp(holder,
																									 shel->cmd[cmd_index]->redir.heredoc.delemiter[(*i)])))
		{
			a = NULL;
			(*i)++;
		}
		if ((*i) >= shel->cmd[cmd_index]->redir.heredoc.her_doc)
		{
			free(a);
			break;
		}
		if (a)
		{
			if (ft_strchr(a, '$') && shel->exapnd_herdoc[(*i)] == 1)
				printf_in_pipe(check_expanding(shel, a), pipes[(*i)][1]);
			else
				printf_in_pipe(a, pipes[(*i)][1]);
		}
		free(a);
	}
}
void run_cmd_h(t_mshel *shel, int cmd_index, int duin, int du,
			   int redirection, int (*pipes)[2], int i)
{
	int tmp_fd;
	int h_number;

	h_number = shel->cmd[cmd_index]->redir.heredoc.her_doc;
	if (shel->cmd_number > 1 || (redirection && shel->cmd[cmd_index]->error ==
													-1))
	{
		if ((redirection == 2 || redirection == 1) && cmd_index == 0)
		{
			dup2(duin, STDIN_FILENO);
			close(duin);
		}
		dup2(du, STDOUT_FILENO);
		close(du);
	}
	if (redirection != 2 && redirection != 1 && shel->cmd[cmd_index]->error == -1)
	{
		tmp_fd = dup(STDIN_FILENO);
		if (i != 0)
		{
			if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
				perror("minisdhell :");
		}
	}
	open_n_close_p(pipes, 1, h_number);
	if (shel->cmd[cmd_index]->cmd && shel->cmd[cmd_index]->error == -1)
		run_cmd(shel, cmd_index, shel->cmd[cmd_index]->cmd);
	if (shel->cmd[cmd_index]->redir.old_input != 0 && (redirection != 2 || redirection != 1) && shel->cmd[cmd_index]->error == -1)
		dup2(tmp_fd, STDIN_FILENO);
}

void ft_heredoc(int cmd_index, t_mshel *shel)
{
	int h_number;
	int du = 0;
	int duin = 0;
	int pipes[shel->cmd[cmd_index]->redir.heredoc.her_doc][2];
	int i;
	char *holder;
	int redirection;

	h_number = shel->cmd[cmd_index]->redir.heredoc.her_doc;
	i = 0;
	holder = NULL;
	open_n_close_p(pipes, 0, h_number);
	redirection = check_redirect_place(shel->cmd[cmd_index]->redir.in,
									   shel->cmd[cmd_index]->redir.out);
	if (shel->cmd_number > 1 || (redirection && shel->cmd[cmd_index]->error ==
													-1))
	{
		if ((redirection == 2 || redirection == 1))
		{
			duin = dup(STDIN_FILENO);
			dup2(shel->cmd[cmd_index]->redir.old_input, STDIN_FILENO);
		}
		du = dup(STDOUT_FILENO);
		dup2(shel->cmd[cmd_index]->redir.old_output, STDOUT_FILENO);
	}
	read_line(shel, cmd_index, &i, pipes);
	run_cmd_h(shel, cmd_index, duin, du, redirection, pipes, i);
}
