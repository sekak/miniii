/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:10 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/13 11:10:10 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char    **alloc_lexer_string(char *input, t_mshel *shel)
{
    char    **string;
    int     count;
    int     i;

    count = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == '|' && input[i])
            count++;
        i++;
    }
    if (!(string = malloc(sizeof(char *) * (count + 1))))
        return (0);
    shel->store_input = ft_strdup(input);
    return (string);
}

void    lexer_part_separate(char **string, t_mshel *shel, t_lexer *newnode, t_lexer *lst)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (string[i])
    {
        if (ft_strncmp(string[i], "|", 2) == 0 && shel->status[i] == 0)
        {
            newnode = add_node(string, j, i + 1);
            ft_add_back(&lst, newnode);
            j = i + 1;
        }
        i++;
    }
    if (i - j >= 1)
    {
        newnode = add_node(string, j, i);
        ft_add_back(&lst, newnode);
    }
    parser(lst, shel, shel->store_input);
}

void lexer(char *input, t_mshel *shel)
{
    char    **string;
    t_lexer *newnode;
    t_lexer *lst;

    lst = NULL;
    newnode = NULL;
    string = alloc_lexer_string(input, shel);
    string = better_parsing(input, shel);
    lexer_part_separate(string, shel, newnode, lst);
}
