/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:45:30 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/19 18:11:14 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_lstnew_k(char *env_val)
{
	t_node	*head;

	head = malloc (sizeof (t_node));
	head->key = NULL;
	head->value_of_the_key = NULL;
	head->key = ft_frontcpy (head->key, env_val, '=');
	head->value_of_the_key = ft_backcpy (head->value_of_the_key, env_val, '=');
	head->equl = 0;
	head->plus = 0;
	head->next = NULL;
	return (head);
}

void	ft_lstadd_front_k(t_node **lst, t_node *new)
{
	new->next = (*lst);
	(*lst) = new;
}

int	ft_lstsize_k(t_node *lst)
{
	t_node	*ptr;
	int		i;

	ptr = lst;
	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

t_node	*ft_lstlast_k(t_node **lst)
{
	t_node	*ptr;

	if (!(*lst))
		return (NULL);
	if ((*lst)->next == NULL)
		return ((*lst));
	ptr = (*lst);
	while (ptr)
	{
		if (ptr->next == NULL)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	ft_lstadd_back_k(t_node **lst, t_node *new)
{
	t_node	*the_last;

	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	the_last = ft_lstlast_k(lst);
	the_last->next = new;
}
