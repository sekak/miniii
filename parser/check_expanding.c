/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expanding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:58:22 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/16 10:34:54 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*check_expanding(t_mshel *shel, char *str)
{
	int		i;
	int		dollar_index;
	char	**tmp;
	char	*value;
	char	*placeholder;

	i = 1;
	dollar_index = find_dollar(str);
	if (!str[dollar_index + 1])
		return (str);
	tmp = ft_split(str, '$');
	value = NULL;
	if (dollar_index == 0)
	{
		i = 0;
		while (tmp[i])
		{
			if (ft_isdigit(tmp[i][0]) || (!ft_isalnum(tmp[i][0]) && (tmp[i][0] != '?' && tmp[i][0] != '_')))
				value = ft_substr(tmp[i], 1, ft_strlen(tmp[i]));
			else if (tmp[i][0] == '?')
			{
				placeholder = ft_strdup(ft_itoa(shel->exit_status));
				if (value)
					value = ft_strjoin(value, placeholder);
				else
					value = ft_strdup(placeholder);
				if (tmp[i][1])
					value = ft_strjoin(value, tmp[i] + 1);
			}
			else
			{
				int k = 0;
				while (tmp[i][k] && (ft_isalnum(tmp[i][k]) || tmp[i][k] == '_'))
					k++;
				placeholder = ft_getenv(shel, ft_substr(tmp[i], 0, k));
				if (placeholder)
				{
					if (value)
						value = ft_strjoin(value, placeholder);
					else
					{
						if (placeholder && placeholder[0])
							value = ft_strdup(placeholder);
					}
				}
				else
					value = NULL;
				if (tmp[i][k])
					value = ft_strjoin(value, ft_substr(tmp[i], k, ft_strlen(tmp[i])));
			}
			i++;
		}
	}
	else if (dollar_index > 0 && tmp)
	{
		value = ft_strdup(tmp[0]);
		while (tmp[i])
		{
			if (ft_isdigit(tmp[i][0]))
				value = ft_strjoin(value, tmp[i] + 1);
			if (tmp[i][0] == '?')
			{
				value = ft_strjoin(value, ft_itoa(shel->exit_status));
				if (tmp[i][1])
					value = ft_strjoin(value, tmp[i] + 1);
			}
			else
			{
				int k = 0;
				while (tmp[i][k] && (ft_isalnum(tmp[i][k]) || tmp[i][k] == '_'))
					k++;

				value = ft_strjoin(value, ft_getenv(shel, ft_substr(tmp[i], 0, k)));
				if (tmp[i][k])
					value = ft_strjoin(value, ft_substr(tmp[i], k, ft_strlen(tmp[i])));
			}
			i++;
		}
	}
	return (value);
}