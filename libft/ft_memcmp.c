/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:18:35 by asekkak           #+#    #+#             */
/*   Updated: 2022/10/15 09:55:08 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*dst;
	const unsigned char	*str;	
	size_t				i;

	dst = (unsigned char *)s1;
	str = (unsigned char *)s2;
	i = 0;
	while (n > i)
	{
		if (dst[i] != str[i])
			return (dst[i] - str[i]);
		i++;
	}
	return (0);
}
