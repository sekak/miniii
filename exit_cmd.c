/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:33:12 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/14 11:44:52 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_utils(char *a)
{
	int	i;

	i = 0;
	if (a[i] == '-' || a[i] == '+')
		i++;
	while (a[i])
	{
		if (!ft_isdigit(a[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_multip(char **a, t_mshel *shel)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if (i > 0)
		{
			print_errors("minishell: exit: too many arguments");
			if (shel->cmd_number == 1)
				return (1);
			else
				exit(1);
		}
		i++;
	}
	return (0);
}

int	check_exit_num(char **a, t_mshel *shel)
{
	char	*tmp;

	if (!exit_utils(a[0]))
	{
		tmp = ft_strjoin("minishell: exit: ", a[0]);
		print_errors(ft_strjoin(tmp, ": numeric argument required"));
		free(tmp);
		if (shel->cmd_number == 1)
			return (255);
		else
			exit(255);
	}
	return (0);
}

int	exit_function(char **a, t_mshel *shel)
{
	int		i;

	i = 0;
	if (!a[0])
		exit(shel->exit_status);
	else
	{
		if (check_exit_num(a, shel) == 255)
			return (255);
		if (check_multip(a, shel) == 1)
			return (1);
		i = 0;
		while (a[i])
		{
			if (ft_isdigit(a[i][0]) || (a[i][0] == '-' && ft_isdigit(a[i][1])))
				exit(ft_atoi(a[i]) % 256);
			i++;
		}
	}
	return (0);
}
