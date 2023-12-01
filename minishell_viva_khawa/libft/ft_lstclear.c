/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:52:35 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 20:58:51 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*helper;

	if (!lst || !*lst || !del)
		return ;
	else
	{
		while (*lst)
		{
			helper = (*lst)-> next;
			del((*lst)-> content);
			free(*lst);
			*lst = helper;
		}
		*lst = NULL;
	}
}
