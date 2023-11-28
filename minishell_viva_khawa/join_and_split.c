/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_and_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 02:17:39 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/28 10:23:14 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_jion_elem(t_token **lst, t_token **lst_new)
{
        ft_lstadd_back2(lst_new, ft_lstnew2(ft_strjoin((*lst)->value, \
                        (*lst)->next->value), WORD));
        (*lst) = (*lst)->next;
        (*lst) = (*lst)->next;
}

t_token *ft_split_lst(t_token *lst)
{
    t_token *new;

    new = NULL;
    while (lst)
    {
        if (lst->type == W_SPC || (lst->type == WORD && lst->value == NULL))
            lst = lst->next;
        else
        {
            ft_lstadd_back2(&new, ft_lstnew2(lst->value, lst->type));
            lst = lst->next;
        }
    }
    return (new);
}

int ft_join_if_need(t_token *lst)
{
    while (lst)
    {
        if (lst->type == WORD && lst->next && (lst->next->type == WORD \
            || lst->next->type == DOLLAR))
            return (1);
        lst = lst->next;
    }
    return (0);
}

t_token *ft_join_needed(t_token *lst)
{
    t_token  *new_lst;

    new_lst = NULL;
    while (lst)
    {
        if (lst->type == WORD && lst->next && (lst->next->type == WORD \
            || lst->next->type == DOLLAR))
            ft_jion_elem(&lst, &new_lst);
        else
        {
            ft_lstadd_back2(&new_lst, ft_lstnew2(lst->value, lst->type));
            lst = lst->next;
        }
    }
    return (new_lst);
}
