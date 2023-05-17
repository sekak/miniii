/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:48:02 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:21:41 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_to_print(int error, char *file)
{
	char	*msg;

	if (error == 13)
		msg = ft_strjoin(file, ft_strjoin(": ", strerror(error)));
	else
		msg = ft_strjoin(strerror(error), "");
	print_errors(ft_strjoin("minishell: ", msg));
}

int	redirect_input(t_mshel *mshel, int cmd_index, int status)
{
	int	fd;
	int	i;

	(void)status;
	i = 0;
	while (mshel->cmd[cmd_index]->redir.input[i])
	{
		if ((!mshel->cmd[cmd_index]->redir.in_file[i]
				|| ft_strchr(mshel->cmd[cmd_index]->redir.in_file[i], ' '))
			&& mshel->cmd[cmd_index]->redir.input_expanded[i] == 1)
		{
			mshel->cmd[cmd_index]->error = -3;
			return (0);
		}
		fd = open(mshel->cmd[cmd_index]->redir.in_file[i], O_RDONLY);
		if (fd == -1)
		{
			mshel->cmd[cmd_index]->error = errno;
			mshel->cmd[cmd_index]->error_file = \
			ft_strdup(mshel->cmd[cmd_index]->redir.in_file[i]);
			return (0);
		}
		if (!mshel->cmd[cmd_index]->redir.input[i + 1])
		{
			if (dup2(fd, STDIN_FILENO) == 1)
				perror("minishell:");
		}
		close(fd);
		i++;
	}
	return (1);
}

int	redirect_output(t_mshel *mshel, int cmd_index)
{
	int	tmp_fd;
	int	i;

	i = 0;
	while (mshel->cmd[cmd_index]->redir.output[i])
	{
		if (!strcmp(mshel->cmd[cmd_index]->redir.output[i], ">>"))
		{
			if ((!mshel->cmd[cmd_index]->redir.out_file[i]
					|| ft_strchr(mshel->cmd[cmd_index]->redir.out_file[i],
						' '))
				&& mshel->cmd[cmd_index]->redir.output_expanded[i] == 1)
			{
				mshel->cmd[cmd_index]->error = -3;
				return (0);
			}
			tmp_fd = open(mshel->cmd[cmd_index]->redir.out_file[i], \
			O_RDWR | O_CREAT | O_APPEND, 0644);
			if (tmp_fd == -1)
			{
				mshel->cmd[cmd_index]->error = errno;
				mshel->cmd[cmd_index]->error_file = \
				ft_strdup(mshel->cmd[cmd_index]->redir.out_file[i]);
				return (0);
			}
		}
		else
		{
			if ((!mshel->cmd[cmd_index]->redir.out_file[i] || \
			ft_strchr(mshel->cmd[cmd_index]->redir.out_file[i], ' '))
				&& mshel->cmd[cmd_index]->redir.output_expanded[i] == 1)
			{
				mshel->cmd[cmd_index]->error = -3;
				return (0);
			}
			tmp_fd = open(mshel->cmd[cmd_index]->redir.out_file[i], \
			O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (tmp_fd == -1)
			{
				mshel->cmd[cmd_index]->error = errno;
				mshel->cmd[cmd_index]->error_file = \
				ft_strdup(mshel->cmd[cmd_index]->redir.out_file[i]);
				return (0);
			}
		}
		if (!mshel->cmd[cmd_index]->redir.output[i + 1])
		{
			if (dup2(tmp_fd, STDOUT_FILENO) == -1)
				perror("minishell:");
		}
		close(tmp_fd);
		i++;
	}
	return (1);
}
