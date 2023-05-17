/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminnette_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:55:25 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:21:09 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hendel_no_quotes(t_mshel *shel,char **new, int *j, char *tmp)
{

	int s = 0;
	new[(*j)++] = parsse_redirection(tmp, &s);
	shel->status[shel->stat++] = 0;
	if (tmp[s])
	{
		if ((*j) != 0 && new[(*j) - 1] && !strcmp(new[(*j) - 1], "<<"))
		{
			shel->exapnd_herdoc[shel->hdoc_num] = 1;
			shel->hdoc_num++;
		}
		char *pointer = substr(tmp, s, ft_strlen(tmp) - (s ));
		new[(*j)++] = check_expanding(shel,pointer);
		free(pointer);
		shel->status[shel->stat++] = 1;
	}
}

void	handel_sing_quote(t_mshel *shel, char *a, int *i,char **new, int *j)
{
	int	checkpoint;

	checkpoint = (*i);
	(*i)++;
	while (a[(*i)] != 39 && a[(*i)])
		(*i)++;
	if ((*j) != 0 && new[(*j) - 1] && !strcmp(new[(*j) - 1], "<<"))
	{
		shel->exapnd_herdoc[shel->hdoc_num] = 0;
		shel->hdoc_num++;
	}
	if (checkpoint != 0 && a[checkpoint - 1] != ' ')
	{
		char *store = substr(a, checkpoint + 1, (*i) - checkpoint - 1);
		if(!store[0] && new[(*j) - 1][ft_strlen(new[(*j) - 1]) - 1] == ' ' && !a[(*i) + 1])
		{
			shel->status[shel->stat - 1] = 0;
			new[(*j) - 1] = ft_strtrim(new[(*j) - 1], " ");
		}
		else
		{
			if(ft_strchr(new[(*j) - 1],' ') && check_space_place(new[(*j) - 1]) == 1)
				new[(*j) - 1] = ft_strjoin(ft_strtr(new[(*j) - 1], " "), store);
			else
				new[(*j) - 1] = ft_strjoin(new[(*j) - 1], store);
		}
	}
	else
	{
		char *tmp;

		tmp = substr(a, checkpoint + 1, (*i) - checkpoint - 1);
		if (ft_strlen(tmp) && (*j) != 0 && theres_is_red(new[(*j) - 1]))
			new[(*j)++] = tmp;
		else if (!ft_strlen(tmp) && (*j) != 0 && theres_is_red(new[(*j) - 1]))
			new[(*j)++] = tmp;
		else if (ft_strlen(tmp))
			new[(*j)++] = tmp;
		else if ((*j) != 0 && !theres_is_red(new[(*j) - 1]))
			new[(*j)++] = NULL;
		else
			new[(*j)++] = ft_calloc(1, 1);
		shel->status[shel->stat++] = 0;
	}
}

void	handel_no_quotes_expand(char *tempo, char **new, int *j, char a, t_mshel *shel)
{
	if (tempo)
	{
		if (new[(*j) - 1])
		{
			if(ft_strlen(tempo) > 1)
			{
				if(a)
					new[(*j) - 1] = ft_strjoin(new[(*j) - 1], tempo);
				else
				{
					if(new[(*j) - 1][0])
					{
						char *tmp = ft_strtrim(tempo, " ");
						new[(*j) - 1] = ft_strjoin(new[(*j) - 1], tmp);
					}
					else
						new[(*j) - 1] = ft_strtr(tempo, " ");
				}
			}
			if(ft_strchr(tempo,' '))
				shel->status[shel->stat - 1] = 1;
		}
		else
		{
			if (ft_strlen(tempo))
			{
				if ((*j) != 0)
				{
					char *l = ft_strtr(tempo," ");
					if(l[0])
						new[(*j) - 1] = l;
					else
					{
						if(!a)
							new[(*j) - 1] = ft_strdup(tempo);
						else
							new[(*j) - 1] = l;
					}
					if(ft_strchr(tempo, ' ') && !a)
						shel->status[shel->stat - 1] = 1;
				}
				else
				{
					if(a)
						new[(*j)++] = ft_strdup(tempo);
					else
						new[(*j)++] = ft_strtrim(tempo, " ");
					if(ft_strchr(tempo, ' ') && !a)
						shel->status[shel->stat - 1] = 1;
				}
			}
			else
			{
				new[(*j) - 1] = NULL;
				shel->status[shel->stat - 1] = 1;
			}
		}
	}
	if ((*j) != 0 && new[(*j) - 1] && !strcmp(new[(*j) - 1], "<<"))
	{
		shel->exapnd_herdoc[shel->hdoc_num] = 1;
		shel->hdoc_num++;
	}
}

void	hendel_no_quotes_spand_j(t_mshel *shel , char *tempo, char **new, int *j, char a)
{
	if (tempo && ft_strchr(tempo, ' '))
	{
		if ((*j) != 0 && !strcmp(new[(*j) - 1], "<<"))
		{
			shel->exapnd_herdoc[shel->hdoc_num] = 1;
			shel->hdoc_num++;
		}
		char **t = ft_split(tempo, ' ');
		if (array_lenth(t) == 1)
		{
			if(a == ' ')
				new[(*j)++] = ft_strtr(tempo, " ");
			else
			{
				if(!a)
				{
					new[(*j)++] = ft_strdup(t[0]);
				}
				else
					new[(*j)++] = ft_strdup(tempo);
			}
			shel->status[shel->stat++] = 1;
		}
		else
		{
			if ((*j) != 0 && !theres_is_red(new[(*j) - 1]))
			{
				new[(*j)++] = ft_strdup(tempo);
				shel->status[shel->stat++] = 1;
			}
			else
			{
				int index = 0;
				if ((*j) != 0 && !strcmp(new[(*j) - 1], "<<"))
					shel->exapnd_herdoc[shel->hdoc_num] = 1;
				if (!t[index])
					new[(*j)++] = ft_calloc(1, 1);
				else
				{
					while (t[index])
					{
						new[(*j)++] = ft_strtrim(t[index], " ");
						shel->status[shel->stat++] = 1;
						index++;
					}
				}
			}
		}
	}
	else if (tempo)
	{
		if ((*j) != 0 && !strcmp(new[(*j) - 1], "<<"))
		{
			shel->exapnd_herdoc[shel->hdoc_num] = 1;
			shel->hdoc_num++;
		}
		new[(*j)++] = ft_strdup(tempo);
		shel->status[shel->stat++] = 1;
	}
	else
	{
		if ((*j) != 0 && !strcmp(new[(*j) - 1], "<<"))
		{
			shel->exapnd_herdoc[shel->hdoc_num] = 1;
			shel->hdoc_num++;
		}
		new[(*j)++] = ft_calloc(1, 1);
		shel->status[shel->stat++] = 1;
	}
}

void	hande_no_quoet_expand_n(t_mshel *shel, char **new, int *j, char *a, int checkpoint, int i)
{
	char *tmp = substr(a, checkpoint, i - checkpoint);
	if (ft_strchr(tmp, '<') || ft_strchr(tmp, '>'))
	{
		int s = 0;
		new[(*j)++] = parsse_redirection(tmp, &s);
		if (tmp[s])
		{
			if ((*j) != 0 && new[(*j) - 1] && !strcmp(new[(*j) - 1], "<<"))
			{
				shel->exapnd_herdoc[shel->hdoc_num] = 1;
				shel->hdoc_num++;
			}
			char *to_befreed = substr(tmp, s, ft_strlen(tmp) - (s));
			new[(*j)++] = ft_strtrim(to_befreed, " ");
			shel->status[shel->stat++] = 0;
			free(to_befreed);
		}
		shel->status[shel->stat++] = 0;
	}
	else
	{
		char *to_befreed =  substr(a, checkpoint, i - checkpoint);
		if ((*j) != 0 && !strcmp(new[(*j) - 1], "<<"))
		{
			shel->exapnd_herdoc[shel->hdoc_num] = 1;
			shel->hdoc_num++;
		}
		if (checkpoint != 0 && a[checkpoint - 1] != ' ')
		{
			new[(*j) - 1] = ft_strjoin(new[(*j) - 1],to_befreed);
			free(to_befreed);
		}
		else
		{
			new[(*j)++] = to_befreed;
			shel->status[shel->stat++] = 0;
		}
	}
	free(tmp);
}
