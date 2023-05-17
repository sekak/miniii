/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:29:39 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/13 13:23:55 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_utils(t_mshel *shel, char *variable)
{
	int		i;
	int		j;
	char	**new_env;
	char	**new_x_env;

	i = 0;
	while (shel->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (shel->env[i])
	{
		if (!ft_strncmp(shel->env[i], variable, ft_strlen(variable))
			&& (shel->env[i][ft_strlen(variable)] == '='
			|| !shel->env[i][ft_strlen(variable)]))
			i++;
		if (shel->env[i])
		{
			new_env[j] = ft_strdup(shel->env[i]);
			i++;
			j++;
		}
	}
	new_env[j] = NULL;
	i = 0;
	while (shel->x_env[i])
		i++;
	new_x_env = malloc(sizeof(char *) * i);
	i = 0;
	j = 0;
	while (shel->x_env[i])
	{
		if (!ft_strncmp(shel->x_env[i], variable, ft_strlen(variable)))
			i++;
		if (shel->x_env[i])
		{
			new_x_env[j] = ft_strdup(shel->x_env[i]);
			i++;
			j++;
		}
	}
	new_x_env[j] = NULL;
	shel->env = new_env;
	shel->x_env = new_x_env;
}

void	ft_unset(t_mshel *shel, int cmd_index)
{
	int	i;

	i = 0;
	while (shel->cmd[cmd_index]->args[i])
	{
		ft_unset_utils(shel, shel->cmd[cmd_index]->args[i]);
		i++;
	}
}

char	*ft_getenv(t_mshel *mshel, char *a)
{
	int		i;
	int		a_len;
	char	*return_value;

	i = 0;
	a_len = ft_strlen(a);
	while (mshel->env[i])
	{
		if (!ft_strncmp(a, mshel->env[i], a_len) && mshel->env[i][a_len] == '=')
		{
			return_value = ft_strchr(mshel->env[i], '=');
			return_value++;
			return (return_value);
		}
		i++;
	}
	return (NULL);
}
