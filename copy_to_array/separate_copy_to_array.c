/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_copy_to_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:46:32 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:38:03 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	sepa_transfer_part_2(t_lexer *lexer, t_mshel *shel, int k, int i)
{
	if (strcmp(lexer->str[shel->start], "<<")
		&& shel->start > 0
		&& shel->cmd[k]->redir.heredoc.her_doc > 0
		&& !strcmp(lexer->str[shel->start - 1], "<<"))
	{
		i = shel->cmd[k]->redir.heredoc.her_doc - 1;
		shel->cmd[k]->redir.heredoc.delemiter[i]
			= ft_strdup(lexer->str[shel->start]);
	}
	else
	{
		shel->cmd[k]->args[shel->i]
			= ft_strdup(lexer->str[shel->start]);
		shel->i++;
	}
}

void	transfer_part_2(t_lexer *lexer, t_mshel *shel, int k)
{
	int	i;

	i = 0;
	if ((!strcmp(lexer->str[shel->start], ">")
			|| !strcmp(lexer->str[shel->start], "<")
			|| !strcmp(lexer->str[shel->start], ">>")
			|| !strcmp(lexer->str[shel->start], "<<"))
		&& shel->status[shel->start] == 0)
		transfer_redirection(lexer, shel, k);
	else
	{
		if (lexer->str[shel->start])
		{
			sepa_transfer_part_2(lexer, shel, k, i);
			shel->start++;
		}
	}
}

void	transfer(t_lexer *lexer, t_mshel *shel, int k, int flag)
{
	while (lexer->str[shel->start])
	{
		if (shel->start == shel->cmd_position)
		{
			shel->start++;
			if (flag)
				shel->start++;
		}
		if (lexer->str[shel->start])
		{
			if (strcmp(lexer->str[shel->start], "|") == 0
				&& shel->start != 0 && shel->status[shel->start] == 0)
				shel->start++;
		}
		if (lexer->str[shel->start])
			transfer_part_2(lexer, shel, k);
	}
	shel->cmd[k]->args[shel->i] = NULL;
	if (lexer->table->redire > 0)
	{
		shel->cmd[k]->redir.input[shel->r] = NULL;
		shel->cmd[k]->redir.in_file[shel->r] = NULL;
		shel->cmd[k]->redir.output[shel->o] = NULL;
		shel->cmd[k]->redir.out_file[shel->o] = NULL;
	}
}
