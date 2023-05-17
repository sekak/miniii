/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:25:02 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/15 14:34:32 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int  count_arg(t_mshel *mshel)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(mshel->store_input[i])
    {
        if(mshel->store_input[i] == ' ')
            count++;
        i++;
    }
    return(count);
}



int  count_expand(t_mshel *mshel, int num)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if(num == 0)
    {
        while(mshel->store_input[i])
        {
            if(mshel->store_input[i] == '<' && mshel->store_input[i + 1] == '<')
                count++;
            i++;
        }
    }
    else if(num == 1)
    {
        while(mshel->store_input[i])
        {
            if(mshel->store_input[i] == '>' && mshel->store_input[i + 1] == '>')
                count++;
            i++;
        }
    }
    return(count);
}

int  count_redir(t_mshel *mshel, int num)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if(num == 0)
    {
        while(mshel->store_input[i])
        {
            if(mshel->store_input[i] == '>')
                count++;
             i++;
        }   
    }
    else if(num == 1)
    {
        while(mshel->store_input[i])
        {
            if(mshel->store_input[i] == '<')
                count++;
             i++;
        }   
    }
    return(count);
}

