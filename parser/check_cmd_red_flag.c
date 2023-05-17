/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_red_flag.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:35:28 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/16 10:34:18 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	check_cmd(t_lexer *head)
{
	int	i;

	i = 0;
	while (head->str[i])
	{
		if (all_cmd(head->str[i]))
		{
			head->cmd = all_cmd(head->str[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	separate_check_flage(int i, int k, t_lexer *head)
{
	while (head->str[i])
	{
		if (ft_strncmp(head->str[i], "-n", 2) == 0)
		{
			k = 0;
			if (head->str[i][k] != '-')
				break ;
			else
				k++;
			while (head->str[i][k] && head->str[i][k] == 'n'
				&& head->str[i][k + 1] == 'n')
				k++;
			if (!head->str[i][k + 1] && head->str[i + 1])
			{
				head->flag = 1;
				break ;
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_flag(t_lexer *head)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	head->flag = 0;
	if (separate_check_flage(i, k, head) == 0)
		return (0);
	return (1);
}

void	separate_redire(int i, int j, t_lexer *lexer)
{
	int	match;

	match = 0;
	while (lexer->str[i])
	{
		lexer->table[j].redire = 0;
		if (choose_red(lexer->str[i]))
		{
			match = ft_strncmp(lexer->str[i],
					choose_red(lexer->str[i]),
					strlen(choose_red(lexer->str[i]) + 1));
			if (match == 0)
			{
				lexer->table[j].redire = 1;
				lexer->table[j].name_file = lexer->str[i + 1];
				lexer->table[j].token_redire
					= choose_red(lexer->str[i]);
				j++;
			}
		}
		i++;
	}
}

int	check_redirection(t_lexer *lexer)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (lexer->str[i])
	{
		if (choose_red(lexer->str[i]))
			count++;
		i++;
	}
	i = 0;
	lexer->table = malloc(sizeof(t_table) * (count + 1));
	if (!lexer->table)
		return (0);
	separate_redire(i, j, lexer);
	return (1);
}
