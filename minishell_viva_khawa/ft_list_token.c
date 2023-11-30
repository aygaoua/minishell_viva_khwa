/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 03:46:00 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 09:22:11 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back2(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst)
		return ;
	last = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		new->prev = last;
        last->next = new;
	}
	new->next = NULL;
}