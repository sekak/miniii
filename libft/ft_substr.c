/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:43:15 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/06 12:51:49 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>

// char *ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t i;
// 	char *ptr;

// 	// bool var = true;
// 	i = 0;
// 	if (!s)
// 		return (0);
// 	if (len > ft_strlen(s))
// 		len = ft_strlen(s);
// 	ptr = malloc(sizeof(char) * (len + 1));
// 	if (!ptr)
// 		return (0);
// 	while (i < len && s[i] && start < ft_strlen(s))
// 	{

// 		if (s[start + i] == 34)
// 		{
// 			start++;
// 			while (s[start + i] != 34)
// 			{
// 				ptr[i] = s[start + i];
// 				i++;
// 			}
// 			if (s[start + i] == 34)
// 				start++;
//  		}
// 		else if (s[start + i] == 39)
// 		{
// 			start++;
// 			while (s[start + i] != 39)
// 			{
// 				ptr[i] = s[start + i];
// 				i++;
// 			}
// 			if (s[start + i] == 39)
// 				start++;

//  		}
// 		else if (i < len)
// 		{
// 			ptr[i] = s[start + i];
// 			i++;
// 		}
//  	}

// 	ptr[i] = '\0';
// 	return (ptr);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			j;
	char			*a;

	i = 0;
	if (!s)
		return (0);
	j = ft_strlen(s);
	a = (char *)malloc(len + 1);
	if (!a)
		return (NULL);
	while (i < len && start < j)
	{
		a[i] = s[i + start];
		i++;
	}
	a[i] = '\0';
	return (a);
}
