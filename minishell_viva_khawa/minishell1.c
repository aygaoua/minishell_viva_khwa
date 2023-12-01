/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:39:21 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 14:42:04 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_make_nodes1(t_token **lst, int *i)
{
	if ((*lst)->type == PIP)
		(*lst) = (*lst)->next;
	while ((*lst) && (*lst)->type != PIP)
	{
		if ((*lst)->type != R_APPEND && (*lst)->type != R_HERDOC \
			&& (*lst)->type != R_IN && (*lst)->type != R_OUT)
			(*i)++;
		else
			(*lst) = (*lst)->next;
		if ((*lst))
			(*lst) = (*lst)->next;
	}
}

void	ft_make_nodes(t_tokens *cmdline, t_token *lst)
{
	int			i;
	int			j;
	t_token		*head;

	while (lst)
	{
		head = lst;
		j = 0;
		i = 0;
		ft_lstadd_back(&cmdline, ft_lstnew(lst->value));
		cmdline = cmdline->next;
		ft_make_nodes1(&lst, &i);
		cmdline->options = malloc((i + 1) * 8);
		if (!cmdline->options)
			return ;
		ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(cmdline->options));
		lst = head;
		ft_make_nodes2(&cmdline, &lst, &j);
	}
}

void	ft_free_clctr(t_collector **lst)
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

void	ft_make_nodes2(t_tokens **cmdline, t_token **lst, int *j)
{
	while ((*lst) && (*lst)->type != PIP)
	{
		if ((*lst)->type != R_APPEND && (*lst)->type != R_HERDOC \
			&& (*lst)->type != R_IN && (*lst)->type != R_OUT)
		{
			(*cmdline)->options[*j] = ft_strdup((*lst)->value);
			(*j)++;
		}
		else
			(*lst) = (*lst)->next;
		if ((*lst))
			(*lst) = (*lst)->next;
	}
	(*cmdline)->options[*j] = NULL;
	if ((*lst))
		(*lst) = (*lst)->next;
}
