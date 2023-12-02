/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 05:03:54 by azgaoua           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/02 00:14:24 by azgaoua          ###   ########.fr       */
=======
/*   Updated: 2023/11/29 23:10:15 by azgaoua          ###   ########.fr       */
>>>>>>> main
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
		ft_exit_status(258);
		return (1);
	}
	return (0);
}

void	ft_print_error_pipe(t_token *lst)
{
	if (lst->next && (lst->next->type == PIP || lst->prev->type == PIP))
		write (2, "minishell: syntax error near unexpected token `||'\n",
			51);
	else
		write (2, "minishell: syntax error near unexpected token `|'\n",
			50);
	ft_exit_status(258);
}

int	ft_check_syntax_error(t_token *lst)
{
	t_token	*head;
	int		q;

<<<<<<< HEAD
	lst = spcless(lst);
	head = lst;
	q = 0;
	while (lst)
	{
		if (lst->type == S_QUOT && q != 2)
			ft_change_q1(&q);
		else if (lst->type == D_QUOT && q != 1)
			ft_change_q2(&q);
		else if (ft_error_syntax(lst, q))
			return (1);
		else if ((lst->type == PIP) && ((!lst->next || !lst->prev) && !q))
			return (ft_print_error_pipe(lst), 1);
		lst = lst->next;
	}
	if (q == 1)
		return (write(2, "minishell: unclosed single quote\n", 34), q);
	else if (q == 2)
		return (write(2, "minishell: unclosed double quote\n", 34), q);
	return (q);
}
=======
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
    return q;
}
>>>>>>> main
