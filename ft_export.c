/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:24:39 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/13 13:23:13 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_extand(char *a, int declare, char *variable)
{
	int	i;

	(void)variable;
	i = 0;
	if (!ft_isalpha(a[0]) && a[0] != '_')
	{
		if (declare)
			print_errors("minishell: not a valid identifier");
		return (0);
	}
	else
	{
		i++;
		if (a[i])
		{
			while (a[i])
			{
				if (!ft_isalnum(a[i]) && a[i] != '_')
				{
					if (declare)
						print_errors("minishell: not a valid identifier");
					return (0);
				}
				i++;
			}
		}
	}
	return (1);
}

int	check_valid(char *a, char *variable, int declare, t_mshel *shel)
{
	int	i;

	(void)shel;
	i = 1;
	if (!a)
	{
		if (declare)
			print_errors("minishell: not a valid identifier");
		return (0);
	}
	if (!check_valid_extand(a, declare, variable))
		return (0);
	return (1);
}

void	free_array(char **a)
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

// add_to_env

int	add_env(t_mshel *shel, char *variable)
{
	int		i;
	char	**var;
	char	**new_env;

	i = 0;
	var = ft_split(variable, '=');
	if (!check_valid(var[0], variable, 1, shel))
		return (0);
	while (shel->env[i])
	{
		if (!ft_strncmp(shel->env[i], var[0], ft_strlen(var[0]))
			&& shel->env[i][ft_strlen(var[0])] == '=')
		{
			free(shel->env[i]);
			shel->env[i] = ft_strdup(variable);
			return (1);
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (shel->env[i])
	{
		new_env[i] = ft_strdup(shel->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(variable);
	i++;
	new_env[i] = NULL;
	free_array(shel->env);
	shel->env = new_env;
	return (1);
}

// add_to_export_env

int	add_x_env(t_mshel *shel, char *variable)
{
	int		i;
	char	**var;
	char	**new_env;

	i = 0;
	var = ft_split(variable, '=');
	if (!var[1] && variable[ft_strlen(variable) - 1] != '=')
	{
		if (!check_valid(var[0], variable, 1, shel))
			return (0);
	}
	else
	{
		if (!check_valid(var[0], variable, 0, shel))
			return (0);
	}
	while (shel->x_env[i])
	{
		if (!ft_strncmp(shel->x_env[i], var[0], ft_strlen(var[0])))
		{
			free(shel->x_env[i]);
			shel->x_env[i] = ft_strdup(variable);
			return (1);
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (shel->x_env[i])
	{
		new_env[i] = ft_strdup(shel->x_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(variable);
	i++;
	new_env[i] = NULL;
	free_array(shel->x_env);
	shel->x_env = new_env;
	return (1);
}

int	ft_export(t_mshel *shel, int cmd_index)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	if (!shel->cmd[cmd_index]->args[i])
		print_env(shel, 1);
	else
	{
		while (shel->cmd[cmd_index]->args[i])
		{
			if (ft_strchr(shel->cmd[cmd_index]->args[i], '=')
				&& (ft_strchr(shel->cmd[cmd_index]->args[i], '=') + 1))
			{
				if (!add_env(shel, shel->cmd[cmd_index]->args[i]))
					state = 1;
				if (!add_x_env(shel, shel->cmd[cmd_index]->args[i]))
					state = 1;
			}
			else
			{
				if (!add_x_env(shel, shel->cmd[cmd_index]->args[i]))
					state = 1;
			}
			i++;
		}
	}
	return (state);
}
