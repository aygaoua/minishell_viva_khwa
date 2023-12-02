/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:08:11 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/02 18:49:37 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_condition(t_token *head)
{
	if (head->type == R_APPEND || head->type == R_HERDOC \
			|| head->type == R_IN || head->type == R_OUT)
		return (1);
	return (0);
}

char	**ft_lst_to_tab(t_token *head)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc ((ft_lstsize(head) + 1) * 8);
	if (!tab)
		return (NULL);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(tab));
	while (head)
	{
		if (ft_condition(head) == 1)
		{
			head = head->next;
			if (head)
				head = head->next;
		}
		else if (head->type == PIP)
			head = head->next;
		else
		{
			tab[i++] = head->value;
			head = head->next;
		}
	}
	return (tab[i] = NULL, tab);
}

int	ft_heredoc_on(t_token *lst)
{
	while (lst)
	{
		if (lst->type == R_HERDOC)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	ft_minishell1(t_tokens **cmdline, t_token **lst, t_node **kmi)
{
	(*lst) = ft_lexer((*cmdline)->input);
	if (ft_check_syntax_error((*lst)))
		return (1);
	(*lst) = ft_expand_and_quots((*lst), *kmi);
	while (ft_join_if_need((*lst)))
		(*lst) = ft_join_needed((*lst));
	(*lst) = ft_split_lst((*lst));
	(*cmdline)->options = ft_lst_to_tab((*lst));
	ft_make_nodes((*cmdline), (*lst));
	ft_heredoc((*lst), (*cmdline));
	ft_in_file((*cmdline), (*lst));
	ft_out_file((*cmdline), (*lst));
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*cmdline;
	t_token		*lst;
	t_node		**kmi;

	kmi = take_env (env);
	cmdline = malloc (sizeof(t_tokens));
	if (!cmdline)
		return (0);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(cmdline));
	cmdline->next = NULL;
	catch_sig();
	while (ac || av)
	{
		cmdline->input = readline("minishell-1$ ");
		if (!cmdline->input)
			return (write(1, "exit\n", 5), exit(0), 0);
		if (cmdline->input[0])
			add_history(cmdline->input);
		cmdline = ft_lstnew(cmdline->input);
		if (ft_minishell1(&cmdline, &lst, kmi))
			continue ;
		if (cmdline->next && cmdline->next->input && cmdline->next->input[0])
			ft_execute_moha(cmdline, kmi);
	}
	return (0);
}
