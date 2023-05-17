/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_lk_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:57:17 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/13 11:10:06 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void ft_sringcpy(char **str, char *content)
{
    int i;

    i = 0;
    while (content[i])
    {
        (*str)[i] = content[i];
        i++;
    }
    (*str)[i] = '\0';
}

t_lexer *add_node(char **content, int start, int end)
{
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    lexer->str = malloc(sizeof(char *) * (end - start + 1));
    if (!lexer)
        return (0);
    for (int i = start; i < end; i++)
    {
        lexer->str[i - start] = malloc(sizeof(char) * (strlen(content[i]) + 1));
        ft_sringcpy(&(lexer->str[i - start]), content[i]);
    }
    lexer->str[end - start] = NULL;
    lexer->next = NULL;
    return (lexer);
}

void ft_add_back(t_lexer **lst, t_lexer *new)
{
    t_lexer *lastnode;

    lastnode = *lst;
    if (*lst)
    {
        while (lastnode->next)
            lastnode = lastnode->next;
        lastnode->next = new;
    }
    else
        *lst = new;
}
