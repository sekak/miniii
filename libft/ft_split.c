/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:23:02 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/06 12:50:39 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdio.h>

// int len_word(char const *s, char c)
// {
// 	int count;
// 	int i;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		if (s[i] == 34 && s[i])
// 		{
// 			count++;
// 			i++;
// 			while (s[i] != 34 && s[i])
// 				i++;
// 		}
// 		else if (s[i] == 39 && s[i])
// 		{
// 			count++;
// 			i++;
// 			while (s[i] != 39 && s[i])
// 				i++;
// 		}
// 		else if (s[i] != 34 && s[i])
// 			count++;
// 		while (s[i] && s[i] != c && s[i])
// 			i++;
// 	}
// 	return (count);
// }

// int len_len_word(char const *s, char c, int i)
// {
// 	int len;
// 	//"med sekak"
// 	len = 0;
// 	while (s[i] && s[i] != c)
// 	{
// 		if (s[i] == 34)
// 		{
//  			i++;			   // 1
// 			while (s[i] != 34) // 9
// 			{
// 				len++;
// 				i++;
// 			}
// 			if (s[i] == 34)
// 			{
// 				i++;
// 				while (s[i] != 34 && s[i] != c) // "
// 				{
// 					i++;
// 					len++;
// 				}
//  			}
// 		}
// 		else if (s[i] == 39)
// 		{
//  			i++;			   // 1
// 			while (s[i] != 39) // 9
// 			{
// 				len++;
// 				i++;
// 			}
// 			if (s[i] == 39)
// 			{
// 				i++;
// 				while (s[i] != 39 && s[i] != c) // "
// 				{
// 					i++;
// 					len++;
// 				}
//  			}
// 		}
// 		else
// 		{
// 			i++;
// 			len++;
// 		}
// 	}
// 	// printf("(i) %d :'%c'  %d: \n",i,s[i],len);

// 	return (len);
// }

// int leword(char const *s, char c, int i)
// {
// 	while (s[i] && s[i] != c)
// 	{
// 		if (s[i] == 34)
// 		{
// 			i++;
// 			while (s[i] != 34)
// 				i++;
// 			if (s[i] == 34)
// 			{
// 				i++;
// 				while (s[i] != 34 && s[i] != c) // 9
// 				{
// 					i++;
//  				}
//   			}
// 		}else if (s[i] == 34)
// 		{
// 			i++;
// 			while (s[i] != 34)
// 				i++;
// 			if (s[i] == 34)
// 			{
// 				i++;
// 				while (s[i] != 34 && s[i] != c) // 9
// 				{
// 					i++;
//  				}
//   			}
// 		}
// 		else
// 			i++;
// 	}
// 	return (i);
// }

// void *ft_free(char **ptr, int j)
// {
// 	while (j-- > 0)
// 		free(ptr[j]);
// 	free(ptr);
// 	return (0);
// }

// // int check_start(char const *s, char c, int i)
// // {
// // 	while (s[i] && s[i] == c)
// // 		i++;
// // 	if (s[i] == 34)
// // 		i++;

// // 	return (i);
// // }

// char **ft_split(char const *s, char c)
// {
// 	char **ptr;
// 	int j;
// 	int i;

// 	j = 0;
// 	i = 0;
// 	if (!s)
// 		return (0);
// 	printf("%s\n",s);
// 	ptr = (char **)malloc(sizeof(char *) * (len_word(s, c) + 1));
// 	// printf("'%d\n'",len_word(s, c));

// 	if (!ptr)
// 		return (0);
// 	while (j < len_word(s, c))
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		ptr[j] = ft_substr(s, i, len_len_word(s, c, i));
// 		// printf("start: %d   end: %d\n",check_start(s,c,i),len_len_word(s, c, i));
// 		if (!ptr)
// 			ft_free(ptr, j);
// 		j++;
// 		i = leword(s, c, i);
// 		// printf("current value i: %d\n",i);
// 	}
// 	ptr[j] = 0;
// 	return (ptr);
// }

// // int main()
// // {
// // 	int i = 0;
// // 	char **split = ft_split("ahmed 'sekak'   ahmd seka",' ');
// // 	while(split[i])
// // 	{
// // 		printf("%s\n",split[i++]);
// // 	}
// // }


int	c_count(const char *s, const char c)
{
	size_t	i;
	int		trgr;
	int		count;

	i = 0;
	trgr = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && trgr == 0)
		{
			count++;
			trgr = 1;
		}
		if (s[i] == c && trgr > 0)
			trgr = 0;
		i++;
	}
	return (count);
}

void	init(int *i, int *j, int *trgr)
{
	*i = 0;
	*j = 0;
	*trgr = 0;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		trgr;
	char	**a;

	if (!s)
		return (NULL);
	init(&i, &j, &trgr);
	a = (char **)malloc(sizeof(char *) * (c_count(s, c) + 1));
	if (a == NULL)
		return (NULL);
	while (s[i])
	{
		trgr = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (i != 0)
			a[j++] = ft_substr(s, trgr, i - trgr);
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	a[j] = NULL;
	return (a);
}
