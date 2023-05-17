/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:21:40 by asekkak           #+#    #+#             */
/*   Updated: 2022/10/18 12:52:36 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*be;
	size_t	i;

	be = (char *)b;
	i = 0;
	while (i < len)
	{
		be[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
