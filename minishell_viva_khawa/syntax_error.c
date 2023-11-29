/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 05:03:54 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/29 14:32:44 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *spcless(t_token *lst)
{
    t_token *spc = NULL;
    while(lst)
    {
        if(lst->type != W_SPC)
            ft_lstadd_back2(&spc, ft_lstnew2(ft_strdup(lst->value), lst->type));
        lst = lst->next;
    }
    return (spc);
}

int ft_check_syntax_error(t_token *lst)
{
    int q = 0;

    lst = spcless(lst);
    while(lst)
    {
        if(lst->type == S_QUOT)
        {
            if(q == 0)
                q = 1;
            else if (q == 1)
                q = 0;
        }
        else if(lst->type == D_QUOT)
        {
            if(q == 0)
                q = 2;
            else if (q == 2)
                q = 0;
        }
        else if(((lst->type == R_APPEND ||
                lst->type == R_HERDOC || lst->type == R_IN || lst->type == R_OUT)) \
                && ((!lst->next) || ((lst->next) && (lst->next->type != WORD \
                && lst->next->type != DOLLAR) && !q)))
            return 1;
        else if((lst->type == PIP) && ((!lst->next || !lst->prev) || ((lst->next && lst->prev) && \
                (lst->next->type == PIP || lst->prev->type == PIP) && !q)))
            return 1;
        lst = lst->next;
    }
    ft_print_token(lst);
    return q;
}