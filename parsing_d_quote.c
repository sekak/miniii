/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_d_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:10:30 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:25:38 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	d_quotes_j(char *tp, char **new, t_mshel *shel, int *j)
{
	char	*to_free;

	if ((*j) != 0)
	{
		if (new[(*j) - 1][0] && tp[0])
		{
			if (ft_strchr(new[(*j) - 1], ' ') && check_space_place \
			(new[(*j) - 1]) == 1 && shel->status[shel->stat - 1] == 1)
			{
				to_free = ft_strtr(new[(*j) - 1], " ");
				new[(*j) - 1] = ft_strjoin(to_free, tp);
				free(to_free);
			}
			else
				new[(*j) - 1] = ft_strjoin(new[(*j) - 1], tp);
		}
		else
		{
			if (tp[0])
				new[(*j) - 1] = ft_strdup(tp);
			else if (!new[(*j) - 1][0])
				new[(*j) - 1] = NULL;
		}
	}
	else
	{
		if (tp)
			new[(*j)++] = tp;
		else
			new[(*j)++] = ft_calloc(1, 1);
	}
}

void	d_quote_expand(char *a, int checkpoint, int *i, int *j, char **new, t_mshel *shel)
{
	char	*exp;
	char	*tet;

	exp = substr(a, checkpoint + 1, (*i) - 1 - checkpoint);
	tet = check_expanding(shel, exp);
	free(exp);
	if (checkpoint != 0 && a[checkpoint - 1] != ' ')
	{
		if (tet)
			new[(*j) - 1] = ft_strjoin(new[(*j) - 1], tet);
	}
	else
	{
		if (tet)
			new[(*j)++] = strdup(tet);
		else
			new[(*j)++] = NULL;
	}
	if (tet)
		free(tet);
	shel->status[shel->stat++] = 0;
}

void	d_quote_copy(t_mshel *shel, int *j, int checkpoint, int *i, char *a, char **new)
{
	char	*to_be_freed;

	to_be_freed = substr(a, checkpoint + 1, (*i) - checkpoint - 1);
	if (ft_strlen(to_be_freed) && (*j) != 0 && theres_is_red(new[(*j) - 1]))
		new[(*j)++] = ft_strdup(to_be_freed);
	else if (!ft_strlen(to_be_freed) && (*j) != 0 && theres_is_red(new[(*j) - 1]))
		new[(*j)++] = ft_strdup(to_be_freed);
	else if (ft_strlen(to_be_freed))
		new[(*j)++] = ft_strdup(to_be_freed);
	else if ((*j) != 0 && !theres_is_red(new[(*j) - 1]))
		new[(*j)++] = NULL;
	else
		new[(*j)++] = ft_calloc(1, 1);
	free(to_be_freed);
	shel->status[shel->stat++] = 0;
}

void	handel_double_quotes(t_mshel *shel, char *a, int *i, int *j, char **new)
{
	int		checkpoint;
	char	*tp;

	checkpoint = *i;
	(*i)++;
	while (a[*i] != 34 && a[*i])
		(*i)++;
	if ((*j) != 0 && new[(*j) - 1] && !strcmp(new[(*j) - 1], "<<"))
	{
		shel->exapnd_herdoc[shel->hdoc_num] = 0;
		shel->hdoc_num++;
	}
	if (ft_strchr(substr(a, checkpoint, (*i) - checkpoint), '$') && a[(*i) - 1] != '$')
		d_quote_expand(a, checkpoint, i, j, new, shel);
	else
	{
		if (checkpoint != 0 && a[checkpoint - 1] != ' ')
		{
			tp = substr(a, checkpoint + 1, (*i) - checkpoint - 1);
			d_quotes_j(tp, new, shel, j);
			free(tp);
		}
		else
			d_quote_copy(shel, j, checkpoint, i, a, new);
	}
}
