/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_output_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:46:32 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/16 10:11:30 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	separate_transfer_input(t_mshel *shel, int k)
{
		shel->cmd[k]->redir.in_file[shel->r] = ft_calloc(1, 1);
		shel->cmd[k]->redir.input_expanded[shel->r]
		= shel->status[shel->start + 1];
		shel->start++;
}

void	transfer_input(t_lexer *lexer, t_mshel *shel, int k)
{
	shel->cmd[k]->redir.in = 1;
	shel->cmd[k]->redir.input[shel->r] = ft_strdup(lexer->str[shel->start]);
	if (lexer->str[shel->start + 1] && !lexer->str[shel->start + 1][0])
	{
		shel->cmd[k]->redir.in_file[shel->r] = NULL;
		shel->cmd[k]->redir.input_expanded[shel->r]
			= shel->status[shel->start + 1];
		shel->start += 1;
	}
	else if (lexer->str[shel->start + 1])
	{
		shel->cmd[k]->redir.in_file[shel->r]
			= ft_strdup(lexer->str[shel->start + 1]);
		shel->cmd[k]->redir.input_expanded[shel->r]
			= shel->status[shel->start + 1];
		shel->start += 2;
	}
	else
		separate_transfer_input(shel, k);
	shel->r++;
}

void	separate_transfer_output(t_mshel *shel, int k)
{
		shel->cmd[k]->redir.out_file[shel->o] = ft_calloc(1, 1);
		shel->cmd[k]->redir.output_expanded[shel->o]
		= shel->status[shel->start + 1];
		shel->start++;
}

void	transfer_output(t_lexer *lexer, t_mshel *shel, int k)
{
	shel->cmd[k]->redir.out = 1;
	shel->cmd[k]->redir.output[shel->o] = ft_strdup(lexer->str[shel->start]);
	if (lexer->str[shel->start + 1] && !lexer->str[shel->start + 1][0])
	{
		shel->cmd[k]->redir.out_file[shel->o] = NULL;
		shel->cmd[k]->redir.output_expanded[shel->o]
			= shel->status[shel->start + 1];
		shel->start += 1;
	}
	else if (lexer->str[shel->start + 1])
	{
		shel->cmd[k]->redir.out_file[shel->o]
			= ft_strdup(lexer->str[shel->start + 1]);
		shel->cmd[k]->redir.output_expanded[shel->o]
			= shel->status[shel->start + 1];
		shel->start += 2;
	}
	else
		separate_transfer_output(shel, k);
	shel->o++;
}
