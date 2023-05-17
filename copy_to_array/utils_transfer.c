/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_transfer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:46:32 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/16 10:12:24 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	input_count(char **a, int state)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (a[i])
	{
		if ((!strcmp(a[i], "<") || !strcmp(a[i], "<<")) && state == 1)
			j++;
		if ((!strcmp(a[i], ">") || !strcmp(a[i], ">")) && state == 0)
			j++;
		i++;
	}
	return (0);
}

int	find_cmd(char **a, t_mshel *shel)
{
	int	i;

	(void)shel;
	i = 0;
	if (!a[0])
		return (-2);
	while (a[i])
	{
		if ((a[i] && (!strcmp(a[i], ">") || !strcmp(a[i], "<")
					|| !strcmp(a[i], ">>") || !strcmp(a[i], "<<")))
			&& shel->status[i] == 0)
			i += (a[i + 1] != NULL) ? 2 : 1;
		else if (a[i] && a[i][0] && !strcmp(a[i], "|") && i != 0)
			i++;
		else if (a[i])
			return (i);
	}
	return (-1);
}

void	alloc_redirect(t_mshel *shel, int i, char **a)
{
	(void)a;
	shel->cmd[i]->redir.output = malloc(sizeof(char *) * 10);
	shel->cmd[i]->redir.out_file = malloc(sizeof(char *) * 10);
	shel->cmd[i]->redir.input_expanded = malloc(sizeof(char *) *10);
	shel->cmd[i]->redir.output_expanded = malloc(sizeof(char *) * 10);
	shel->cmd[i]->redir.input = malloc(sizeof(char *) * 10);
	shel->cmd[i]->redir.in_file = malloc(sizeof(char *) * 10);
	shel->cmd[i]->redir.heredoc.cmd = ft_calloc(1, 1);
	shel->cmd[i]->redir.heredoc.delemiter = malloc(sizeof(char *) * 10);
}

void	transfer_redirection(t_lexer *lexer, t_mshel *shel, int k)
{
	if (!strcmp(lexer->str[shel->start], "<"))
		transfer_input(lexer, shel, k);
	if (lexer->str[shel->start] && !strcmp(lexer->str[shel->start], "<<"))
	{
		shel->cmd[k]->redir.heredoc.her_doc++;
		shel->start++;
	}
	if (lexer->str[shel->start] && (!strcmp(lexer->str[shel->start], ">")
			|| !strcmp(lexer->str[shel->start], ">>")))
		transfer_output(lexer, shel, k);
}

void	transfer_herdoc_args(t_mshel *shel, int i, t_lexer *head)
{
	if (shel->cmd[i]->cmd)
		shel->cmd[i]->redir.heredoc.cmd
			= ft_strdup(shel->cmd[i]->cmd);
	if (head->str[shel->cmd_position + 1]
		&& strcmp(head->str[shel->cmd_position + 1], "<<"))
		shel->cmd[i]->redir.heredoc.cmd
			= ft_strjoin(shel->cmd[i]->redir.heredoc.cmd, \
		ft_strjoin(" ", head->str[shel->cmd_position + 1]));
}
