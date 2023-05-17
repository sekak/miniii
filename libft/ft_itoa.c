/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:39:38 by asekkak           #+#    #+#             */
/*   Updated: 2022/10/18 15:31:09 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(long nb)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*work(long nb, char *new, int j)
{
	int		i;
	char	num[13];

	i = 0;
	while (nb > 0)
	{
		num[i] = (nb % 10) + 48;
		nb = nb / 10;
		i++;
	}
	while (i-- > 0)
		new[j++] = num[i];
	new[j] = '\0';
	return (new);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		j;
	char	*new;

	j = 0;
	nb = n;
	new = malloc(sizeof(char) * (len(nb) + 1));
	if (!new)
		return (0);
	if (nb == 0)
	{
		new[0] = '0';
		new[1] = '\0';
		return (new);
	}
	else if (nb < 0)
	{
		new[0] = '-';
		nb *= -1;
		++j;
	}
	return (work(nb, new, j));
}
