/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:36:06 by asekkak           #+#    #+#             */
/*   Updated: 2022/10/15 11:12:31 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{	
	char	*new;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (src[size])
		size++;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
