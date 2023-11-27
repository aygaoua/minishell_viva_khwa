/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:20:03 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/27 05:00:54 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_lstnew(char *str)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (0);
	new->cmd = str;
	new->input = str;
	new->i_file = NULL;
	new->o_file = NULL;
	new->options = NULL;
	new->dlmtr = NULL;
	new->i_fd = -2;
	new->o_fd = -2;
	new->type_i = -2;
	new->type_o = -2;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstnew2(char *v, token_type t)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->type = t;
	new->value = v;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*last;

	if (!lst)
		return ;
	last = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last -> next;
		last -> next = new;
	}
}

void	ft_lstdelone(t_tokens *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->input);
		free(lst);
	}
}

t_tokens	*ft_lstlast(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_tokens *lst)
{
	t_tokens	*j;
	int			i;

	if (!lst)
		return (0);
	j = lst;
	i = 0;
	while (j != NULL)
	{
		j = lst -> next;
		lst = j;
		i++;
	}
	return (i);
}
