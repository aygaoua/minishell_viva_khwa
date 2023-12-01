/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 05:03:54 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 21:05:54 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*spcless(t_token *lst)
{
	t_token	*spc;

	spc = NULL;
	while (lst)
	{
		if (lst->type != W_SPC)
			ft_lstadd_back2(&spc, ft_lstnew2(ft_strdup(lst->value), lst->type));
		lst = lst->next;
	}
	return (spc);
}

int	ft_error_syntax(t_token *lst, int q)
{
	if (((lst->type == R_APPEND || lst->type == R_HERDOC \
			|| lst->type == R_IN || lst->type == R_OUT)) && ((!lst->next) \
			|| ((lst->next) && (lst->next->type != WORD \
			&& lst->next->type != DOLLAR && lst->next->type != S_QUOT \
			&& lst->next->type != D_QUOT) && !q)))
	{
		if (lst->type == R_APPEND)
			write(2, "minishell: syntax error near unexpected token `>>'\n", 51);
		else if (lst->type == R_HERDOC)
			write(2, "minishell: syntax error near unexpected token `<<'\n", 51);
		else if (lst->type == R_IN)
			write(2, "minishell: syntax error near unexpected token `<'\n", 50);
		else if (lst->type == R_OUT)
			write(2, "minishell: syntax error near unexpected token `>'\n", 50);
		return (1);
	}
	return (0);
}

int	ft_check_syntax_error(t_token *lst)
{
	t_token	*head;
	int		q;

	lst = spcless(lst);
	head = lst;
	q = 0;
	while (lst)
	{
		if (lst->type == S_QUOT && q != 2)
		{
			if (q == 0)
				q = 1;
			else if (q == 1)
				q = 0;
		}
		else if (lst->type == D_QUOT && q != 1)
		{
			if (q == 0)
				q = 2;
			else if (q == 2)
				q = 0;
			printf("%d\n", q);
		}
		else if (ft_error_syntax(lst, q))
			return (1);
		else if ((lst->type == PIP) && ((!lst->next || !lst->prev) && !q))
		{
			if (lst->next && (lst->next->type == PIP || lst->prev->type == PIP))
				write (2, "minishell: syntax error near unexpected token `||'\n",
					51);
			else
				write (2, "minishell: syntax error near unexpected token `|'\n",
					50);
			return (1);
		}
		lst = lst->next;
	}
	if (q == 1)
	{
		write(2, "minishell: unclosed single quote\n", 34);
		return (q);
	}
	else if (q == 2)
	{
		write(2, "minishell: unclosed double quote\n", 34);
		return (q);
	}
	printf("%d\n", q);
	return (q);
}
