/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:26:46 by asekkak           #+#    #+#             */
/*   Updated: 2022/10/18 12:47:59 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	total;

	total = count * size;
	if (size && total / size != count)
		return (0);
	ptr = (void *)malloc((total));
	if (!ptr)
		return (0);
	ft_bzero(ptr, total);
	return (ptr);
}
