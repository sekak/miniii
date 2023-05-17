/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:26:40 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/10 21:27:30 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_set(int c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	first_p;
	size_t	last_p;
	size_t	i;

	i = 0;
	first_p = 0;
	if (s1 == NULL)
		return (0);
	if (set == NULL)
		return (ft_strdup(s1));
	last_p = ft_strlen(s1);
	while (s1[i] && in_set(s1[first_p], set))
	{
		if(s1[i + 1] != ' ' || !s1[i + 1])
			break;
		first_p++;
	}
	while (last_p > first_p && in_set(s1[last_p - 1], set))
	{
		if(s1[last_p - 1] != ' ')
			break;
		last_p--;
	}
	new = malloc(sizeof(char) * (last_p - first_p + 1));
	if (new == NULL)
		return (NULL);
	while (last_p > first_p)
		new[i++] = s1[first_p++];
	new[i] = '\0';
	return (new);
}
