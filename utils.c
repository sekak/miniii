/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:25:37 by mkhairou          #+#    #+#             */
/*   Updated: 2023/05/15 12:21:47 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_space_place(char *a)
{
	int	i;

	i = 1;
	if (a[0] == ' ' && a[ft_strlen(a)] == ' ')
		return (0);
	if (a[0] == ' ')
		return (1);
	else
		return (2);
}

char	*ft_strtr(char *s1, char *set)
{
	int		i;
	int		len;
	char	*a;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1) - 1;
	while (len > 0 && ft_strchr(set, s1[len]))
		len--;
	a = ft_substr(s1, 0, len + 1);
	return (a);
}

int	array_lenth(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

int	theres_is_red(char *a)
{
	if (!a)
		return (1);
	if (!strcmp(a, "<") || !strcmp(a, "<<") || !strcmp(a, ">") || !strcmp(a,
			">>"))
		return (0);
	return (1);
}

void	print_errors(char *a)
{
	write(2, a, ft_strlen(a));
	write(2, "\n", 1);
}

// long	checking_overwrite(t_mshel *shel, int cmd_index)
// {
// 	int		fd[2];
// 	char	buffer[1000000];
// 	ssize_t	n;
// 	int		i;
// 	int		tmp;
// 	ssize_t	size;

// 	pipe(fd);
// 	if (fork() == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		run_cmd(shel, cmd_index, shel->cmd[cmd_index]->cmd);
// 		sleep(1);
// 		exit(0);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		n = read(fd[0], buffer, 1000000);
// 		buffer[n] = '\0';
// 	}
// 	i = 0;
// 	while (shel->cmd[cmd_index]->redirect.out_file[i])
// 	{
// 		if (!shel->cmd[cmd_index]->redirect.out_file[i + 1])
// 			break ;
// 		i++;
// 	}
// 	tmp = open(shel->cmd[cmd_index]->redirect.out_file[i], O_RDONLY);
// 	size = read(tmp, buffer, 1024);
// 	close(tmp);
// 	return ((long)n - (long)size);
// }

void	no_quot_part(char *a, t_mshel *shel, int *i, int *j, char **new)
{
	char	*tmp;
	char	*tempo;
	int		checkpoint;

	checkpoint = *i;
	while (a[(*i)] != '\0' && a[(*i)] != 39 && a[(*i)] != 34 && a[(*i)] != ' ')
		(*i)++;
	if ((*i) > checkpoint)
	{
		tmp = substr(a, checkpoint, (*i) - checkpoint);
		if (ft_strchr(tmp, '$'))
		{
			if (ft_strchr(tmp, '<') || ft_strchr(tmp, '>'))
				hendel_no_quotes(shel, new, j, tmp);
			else
			{
				char *trimed = ft_strtrim(tmp, " ");
				tempo = check_expanding(shel, trimed);
				free(trimed);
				if (checkpoint != 0 && a[checkpoint - 1] != ' ')
					handel_no_quotes_expand(tempo, new, j, a[(*i)], shel);
				else
					hendel_no_quotes_spand_j(shel, tempo, new, j,
							a[(*i)]);
				if(tempo)
					free(tempo);
			}
		}
		else
			hande_no_quoet_expand_n(shel, new, j, a, checkpoint, *i);
		free(tmp);
	}
}

char	*substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	if (!s)
		return (0);
	j = ft_strlen(s);
	a = (char *)malloc(len + 1);
	if (!a)
		return (NULL);
	while (s[i] && i < len && start < j)
	{
		a[i] = s[i + start];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	**better_parsing(char *a, t_mshel *shel)
{
	int		i;
	int		j;
	int		checkpoint;
	char	**new;

	j = 0;
	i = 0;
	shel->stat = 0;
	new = ft_calloc(1024, 1024);
	shel->hdoc_num = 0;
	while (a[i])
	{
		checkpoint = i;
		if (a[i] != 39 && a[i] != 34)
			no_quot_part(a, shel, &i, &j, new);
		checkpoint = i;
		if (a[i] == 39 || a[i] == 34)
		{
			if (a[i] == 39)
				handel_sing_quote(shel, a, &i, new, &j);
			else if (a[i] == 34)
				handel_double_quotes(shel, a, &i, &j, new);
		}
		if (a[i] == 0)
			break ;
		i++;
	}
	new[j] = NULL;
	return (new);
}
