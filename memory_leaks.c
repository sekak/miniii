/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_leaks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:59:02 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:25:19 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

void	free_all(t_mshel *shel, int size)
{
	int	i;
	i = 0;
	while (i < size)
	{
		free(shel->cmd[i]->cmd);
		free_args(shel->cmd[i]->args);
		if(shel->cmd[i]->redir.in || shel->cmd[i]->redir.out)
		{
			free_args(shel->cmd[i]->redir.input);
			free_args(shel->cmd[i]->redir.in_file);
			free(shel->cmd[i]->redir.input_expanded);
			free_args(shel->cmd[i]->redir.output);
			free_args(shel->cmd[i]->redir.out_file);
			free(shel->cmd[i]->redir.heredoc.cmd);
			free(shel->cmd[i]->redir.output_expanded);
			free(shel->cmd[i]->redir.heredoc.delemiter);
		}
		free(shel->cmd[i]);
		i++;
	}
	free(shel->cmd);
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer *head;

	while (lexer)
	{
		free_args(lexer->str);
		free(lexer->table);
		head = lexer;
		lexer = lexer->next;
		free(head);
	}
}
