/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:56:24 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/13 13:14:19 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	string_to_print(char *a)
{
	int	i;

	i = -1;
	while (a[++i])
		write(1, &a[i], 1);
}

void	ech_o(t_mshel *shel, int i)
{
	int	j;

	j = 0;
	while (shel->cmd[i]->args[j] && !ft_strncmp(shel->cmd[i]->args[j], "-n", \
	ft_strlen(shel->cmd[i]->args[j])))
		j++;
	while (shel->cmd[i]->args[j])
	{
		string_to_print(shel->cmd[i]->args[j]);
		j++;
		if (shel->cmd[i]->args[j] && shel->cmd[i]->args[j][0])
			write(1, " ", 1);
	}
	if (shel->cmd[i]->flags != 1)
		write(1, "\n", 1);
}

void	print_export(t_mshel *shel, int i, int k)
{
	printf("%c", shel->x_env[i][k]);
	k++;
	printf("\"");
	while (shel->x_env[i][k])
	{
		if (!ft_isalnum(shel->x_env[i][k]) && ft_strchr("$\"", \
		shel->x_env[i][k]))
			printf("\\");
		printf("%c", shel->x_env[i][k]);
		k++;
	}
	printf("\"");
	printf("\n");
}

void	print_env(t_mshel *shel, int stat)
{
	int	i;
	int	k;

	i = -1;
	if (!stat)
	{
		while (shel->env[++i])
			printf("%s\n", shel->env[i]);
	}
	else
	{
		while (shel->x_env[++i])
		{
			k = 0;
			printf("declare -x ");
			while (shel->x_env[i][k] && shel->x_env[i][k] != '=')
				printf("%c", shel->x_env[i][k++]);
			if (!shel->x_env[i][k])
				printf("\n");
			else
				print_export(shel, i, k);
		}
	}
}
