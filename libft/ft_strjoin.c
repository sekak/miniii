/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:54:41 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/08 12:50:37 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
    int i, len_2, j;
    char *ptr;

    i = 0;
    j = 0;
    if (s1 == NULL && s2 == NULL)
        return (NULL);
    len_2 = (s2 == NULL || s2[0] == '\0') ? 1 : ft_strlen(s2);
    ptr = malloc(sizeof(char) * (ft_strlen(s1) + len_2 + 1));
    if (!ptr)
        return (NULL);
    while (s1[i])
    {
        ptr[i] = s1[i];
		// printf("here: %s\n",s1);
        i++;
    }
    while (s2 && s2[j])
    {
        ptr[i + j] = s2[j];
        j++;
    }
    ptr[i + j] = '\0';
    return (ptr);
}


