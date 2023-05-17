/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:25:53 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/16 10:27:25 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_file(int i, char *a)
{
	int	state;

	state = 0;
	while (i)
	{
		if (ft_isalnum(a[i]) || a[i] == '\'' || a[i] == '\"')
			state = 1;
		i--;
	}
	return (state);
}

int	print_error(int cho)
{
	if (cho == 0)
		print_errors("minishell: syntax error ");
	else if (cho == 1)
		print_errors("minishell: unexpected EOF while looking for matching");
	return (0);
}

int	separate_check_syntaxe(char *a, t_mshel *shel)
{
	if (shel->j == 0 || a[shel->j + 1] == '\0' || a[shel->j - 1] == '|')
	{
		if (shel->j == 0 && a[shel->j] != '<' && a[shel->j] != '>')
			return (print_error(0));
		else if (!a[shel->j + 1])
			return (print_error(0));
	}
	else if (a[shel->j] == '<' && a[shel->j + 1] == '>')
		return (print_error(0));
	else if (a[shel->j] == '>' && a[shel->j + 1] == '<')
		return (print_error(0));
	else if (a[shel->j] == '|' && !find_file(shel->j, a))
		return (print_error(0));
	else
		shel->prev_symbol = 1;
	return (1);
}

int	check_syntax(char *a, t_mshel *shel)
{
	while (a[shel->j])
	{
		if (a[shel->j] == ' ' && !a[shel->j + 1]
			&& !shel->quotes && shel->prev_symbol)
			return (print_error(0));
		if (a[shel->j] == '"' || a[shel->j] == '\'')
		{
			if (!shel->quotes)
				shel->quotes = a[shel->j];
			else if (shel->quotes == a[shel->j])
				shel->quotes = 0;
		}
		else if (!shel->quotes && (a[shel->j] == '<'
				|| a[shel->j] == '>' || a[shel->j] == '|' || a[shel->j] == 92))
			return (separate_check_syntaxe(a, shel));
		else
			shel->prev_symbol = 0;
		shel->j++;
	}
	if (shel->quotes != 0)
		return (print_error(1));
	return (1);
}
