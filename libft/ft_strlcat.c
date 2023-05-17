/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:04:04 by asekkak           #+#    #+#             */
/*   Updated: 2022/10/18 10:41:09 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (!dst && dstsize == 0)
		return (0);
	while (dst[count])
		count++;
	if (dstsize == 0 || count > dstsize)
		return (ft_strlen(src) + dstsize);
	while (i < (dstsize - count - 1) && src[i] && count < dstsize)
	{
		dst[count + i] = src[i];
		i++;
	}
	dst[i + count] = '\0';
	return (count + ft_strlen(src));
}
