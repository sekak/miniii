/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:46:32 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:24:04 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	separate_transfer_cmd(t_mshel *shel, t_lexer *hed, int i)
{
	shel->cmd[i]->redir.heredoc.her_doc = 0;
	shel->cmd_position = find_cmd(hed->str, shel);
	if (shel->cmd_position == -1)
		shel->cmd[i]->cmd = NULL;
	else
		shel->cmd[i]->cmd = ft_strdup(hed->str[shel->cmd_position]);
	shel->cmd[i]->redir.in = 0;
	shel->cmd[i]->redir.out = 0;
	if (hed->flag != 0)
		shel->cmd[i]->flags = 1;
	if (hed->table->redire > 0)
		alloc_redirect(shel, i, hed->str);
	if (hed->flag != 0)
		transfer(hed, shel, i, 1);
	else
		transfer(hed, shel, i, 0);
	if (shel->cmd[i]->redir.heredoc.her_doc > 0)
		transfer_herdoc_args(shel, i, hed);
}

void	transfer_cmd(t_lexer *lexer, t_mshel *shel)
{
	int		i;
	int		j;
	t_lexer	*head;

	i = 0;
	head = lexer;
	while (head)
	{
		j = 0;
		separate_transfer_cmd(shel, head, i);
		i++;
		head = head->next;
	}
	shel->cmd_number = i;
}

void	dup_env(t_mshel *shel, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	shel->env = malloc(sizeof(char *) * (i + 1));
	shel->x_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		shel->x_env[i] = ft_strdup(env[i]);
		shel->env[i] = ft_strdup(env[i]);
		i++;
	}
	shel->x_env[i] = NULL;
	shel->env[i] = NULL;
}

void	separate_transfer_to_array(t_mshel *mshel, int i)
{
	mshel->cmd[i] = malloc(sizeof(t_cmd));
	mshel->cmd[i]->args = malloc(sizeof(char *) * 101);
	mshel->cmd[i]->error = -1;
	mshel->cmd[i]->redir.old_output = 0;
	mshel->cmd[i]->redir.old_input = 0;
	mshel->cmd[i]->redir.ambugius = 0;
}

void	transfer_to_array(t_lexer *lexer, int size_arrays, t_mshel *mshel)
{
	int	pipe[0][2];
	int	i;

	mshel->cmd = malloc(sizeof(t_cmd *) * size_arrays);
	if (!mshel->cmd)
	{
		printf("Failed to allocate memory for mshel->cmd\n");
		exit(1);
	}
	i = 0;
	while (i < size_arrays)
	{
		separate_transfer_to_array(mshel, i);
		i++;
	}
	transfer_cmd(lexer, mshel);
	free_lexer(lexer);
	if (mshel->cmd_number == 1)
		execute_cmd(mshel, pipe, 0, 0);
	else
		pipe_and_start(mshel);
	free_all(mshel, size_arrays);
}
