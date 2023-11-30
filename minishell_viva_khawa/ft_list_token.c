/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 03:46:00 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 11:53:12 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_collector	*ft_lstnew_clctr(void *lst)
{
	t_collector	*new;

	new = malloc(sizeof(t_collector));
	if (!new)
		return (0);
	new->ptr = lst;
	new->next = NULL;
	return (new);
}

void	ft_free_collector(t_collector **lst)
{
	t_collector	*head;
	t_collector	*tmp;

	if (!lst || !*lst)
		return ;
	head = *lst;
	while (*lst)
	{
		tmp = head->next;
		free(head->ptr);
		free(head);
		head = tmp;
	}
}

void	ft_lstadd_back_clctr(t_collector **lst, t_collector *new)
{
	t_collector	*last;

	if (!lst)
		return ;
	last = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
        last->next = new;
	}
	new->next = NULL;
}

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