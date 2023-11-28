/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_and_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 02:17:39 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/28 03:52:59 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_jion_elem(t_token **lst, t_token **lst_new)
{
        ft_lstadd_back2(lst_new, ft_lstnew2(ft_strjoin((*lst)->value, \
                        (*lst)->next->value), WORD));
        (*lst) = (*lst)->next;
        (*lst) = (*lst)->next;
    // printf("------------%s-------------\n", (*lst_new)->value);
}

t_token *ft_join_and_split(t_token *lst)
{
    t_token  *new_lst;

    new_lst = NULL;
    while (lst)
    {
        printf("------------%s-------------\n", lst->value);
        if (lst->type == WORD && lst->next && (lst->next->type == WORD \
            || lst->next->type == DOLLAR))
        {
            ft_jion_elem(&lst, &new_lst);
            new_lst = ft_join_and_split(new_lst);
        }
        else
        {
            ft_lstadd_back2(&new_lst, ft_lstnew2(lst->value, lst->type));
            lst = lst->next;
        }
        // else
        // {
        // }
    }
    return (new_lst);
}
