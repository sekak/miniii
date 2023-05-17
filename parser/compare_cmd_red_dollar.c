/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_cmd_red_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:35:28 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/16 10:36:14 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*all_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 6) == 0)
		return ("echo");
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return ("cd");
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return ("pwd");
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return ("export");
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return ("unset");
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return ("env");
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return ("exit");
	return (0);
}

char	*all_redir(char *redir)
{
	if (ft_strncmp(redir, ">", 6) == 0)
		return ("echo");
	else if (ft_strncmp(redir, ">>", 3) == 0)
		return ("cd");
	else if (ft_strncmp(redir, "<", 4) == 0)
		return ("pwd");
	else if (ft_strncmp(redir, "<<", 7) == 0)
		return ("export");
	return (0);
}

char	*choose_red(char *red)
{
	if (ft_strncmp(red, ">", 2) == 0)
		return (">");
	else if (ft_strncmp(red, "<", 2) == 0)
		return ("<");
	else if (ft_strncmp(red, ">>", 3) == 0)
		return (">>");
	else if (ft_strncmp(red, "<<", 3) == 0)
		return ("<<");
	return (0);
}

int	find_dollar(char *a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if (a[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}
