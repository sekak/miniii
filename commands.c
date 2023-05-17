/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:31:38 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/14 13:33:17 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**mini_split(char *a)
{
	int		i;
	char	**val;

	i = 0;
	while (a[i] && a[i] != ' ')
		i++;
	if (!ft_strncmp(ft_substr(a, 0, i), "awk", i))
	{
		val = malloc(sizeof(char *) * 3);
		while (a[i] && a[i] != ' ')
			i++;
		val[0] = ft_substr(a, 0, i);
		if (a[i])
		{
			val[1] = ft_substr(a, i + 1, ft_strlen(a));
			val[2] = NULL;
		}
		else
			val[1] = NULL;
	}
	else
		val = ft_split(a, ' ');
	return (val);
}

int	c_d(t_mshel *shel, char *a)
{
	int	ret;

	if (!a)
	{
		a = ft_getenv(shel, "HOME");
		if (!a)
		{
			print_errors("minishell: cd: HOME not set");
			return (1);
		}
	}
	if (!ft_strncmp(a, "~", 1))
		a = ft_strjoin("/Users/", ft_getenv(shel, "USER"));
	ret = chdir(a);
	if (ret == -1)
	{
		print_errors(ft_strjoin("minishell:", " No such file or directory"));
		return (1);
	}
	return (0);
}

void	p_w_d(void)
{
	char	a[PATH_MAX];
	int		i;

	getcwd(a, sizeof(a));
	i = 0;
	while (a[i])
	{
		write(1, &a[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	free_path(char **path, int i)
{
	while (path[i])
	{
		free(path[i++]);
	}
}

char	*join_cnp(char *a, char *b)
{
	char	*ret;
	char	*p;

	ret = ft_strjoin(a, "/");
	free(a);
	p = ret;
	ret = ft_strjoin(ret, b);
	free(p);
	return (ret);
}

void	execute_shell(char **cmd, t_mshel *shel)
{
	char	*path;
	char	**tmp_path;
	char	*p;
	int		i;

	i = 0;
	path = ft_getenv(shel, "PATH");
	if (cmd[0][0] == '/' || (cmd[0][0] == '.'))
	{
		if (execve(cmd[0], cmd, shel->env) == -1)
		{
			print_errors(ft_strjoin("minishell: ", strerror(errno)));
			exit(127);
		}
	}
	if (path)
	{
		tmp_path = ft_split(path, 58);
		while (tmp_path[i])
		{
			p = join_cnp(tmp_path[i], cmd[0]);
			if (!access(p, F_OK))
				execve(p, cmd, shel->env);
			free(p);
			i++;
		}
	}
	if (path)
		print_errors("minishell: command not found");
	else
		print_errors("minishell: No such file or directory");
	exit(127);
}
