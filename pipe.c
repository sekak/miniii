/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 22:48:51 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:24:37 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect_place(int in, int out)
{
	if (in == 1 && out == 1)
		return (1);
	else if (in == 1)
		return (2);
	else if (out == 1)
		return (3);
	else
		return (0);
}

int	redirecrect_m(int red_status, t_mshel *shel, int (*pipe)[2], int i)
{
	if (red_status == 2)
	{
		if (!redirect_input(shel, i, 0))
			return (0);
	}
	if (red_status != 2)
	{
		if (dup2(pipe[i - 1][0], STDIN_FILENO) == -1)
			perror("minishell :");
	}
	if (red_status == 3)
		redirect_output(shel, i);
	if (red_status != 3)
	{
		if (dup2(pipe[i][1], STDOUT_FILENO) == -1)
			perror("minishell :");
	}
	return (1);
}

int	redirect_l(int red_status, t_mshel *shel, int (*pipe)[2], int i)
{
	if (red_status == 2)
	{
		if (!redirect_input(shel, i, 0))
			return (0);
	}
	if (red_status != 2)
	{
		if (dup2(pipe[i - 1][0], STDIN_FILENO) == -1)
			perror("minishell :");
	}
	if (red_status == 3)
		redirect_output(shel, i);
	return (1);
}

int	redirect_to_pipe(t_mshel *shel, int (*pipe)[2], int i, int red_status,
		int status)
{
	shel->cmd[i]->redir.old_input = dup(STDIN_FILENO);
	shel->cmd[i]->redir.old_output = dup(STDOUT_FILENO);
	if (i == 0)
	{
		if (red_status == 2)
		{
			if (!redirect_input(shel, i, 0))
				return (0);
		}
		if (red_status == 3)
		{
			if (!redirect_output(shel, i))
				return (0);
		}
		if (red_status != 3 && status != 0)
		{
			if (dup2(pipe[i][1], STDOUT_FILENO) == -1)
				perror("minishell :");
		}
	}
	if (i > 0)
	{
		if (i + 1 < shel->cmd_number)
			redirecrect_m(red_status, shel, pipe, i);
		else
			redirect_l(red_status, shel, pipe, i);
	}
	return (1);
}

void	check_herdoc(t_mshel *mshel, int (*pipes)[2])
{
	int	i;
	int	id;

	i = 0;
	while (i < mshel->cmd_number)
	{
		if (mshel->cmd[i]->redir.heredoc.her_doc > 0)
		{
			id = fork();
			if (id == -1)
				printf("minishell : %s\n", strerror(errno));
			if (id == 0)
				execute_cmd(mshel, pipes, i, 1);
			else
				wait(NULL);
		}
		i++;
	}
}

void	create_proc(t_mshel *mshel, int (*pipes)[2], int *pid)
{
	int	i;
	int	id;

	i = 0;
	while (i < mshel->cmd_number)
	{
		if (mshel->cmd[i]->redir.heredoc.her_doc > 0)
			i++;
		id = fork();
		if (id == -1)
			printf("minishell : %s\n", strerror(errno));
		if (id == 0)
			execute_cmd(mshel, pipes, i, 1);
		else
			pid[i] = id;
		i++;
	}
}

void	pipe_and_start(t_mshel *mshel)
{
	int	i;
	int	status;
	int	pid[mshel->cmd_number];
	int	pipes[mshel->cmd_number][2];

	i = 0;
	status = 0;
	open_n_close_p(pipes, 0, mshel->cmd_number - 1);
	check_herdoc(mshel, pipes);
	create_proc(mshel, pipes, pid);
	open_n_close_p(pipes, 1, mshel->cmd_number - 1);
	i = 0;
	while (i < mshel->cmd_number)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	mshel->exit_status = WEXITSTATUS(status);
}
