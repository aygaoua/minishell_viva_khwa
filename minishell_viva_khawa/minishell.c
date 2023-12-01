/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:08:11 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 19:03:26 by azgaoua          ###   ########.fr       */
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

void	ft_debug(t_tokens *nodes)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (nodes)
	{
		printf ("in_fd %d = ---\'%d\'---\n", j, nodes->i_fd);
		printf ("out_fd %d = ---\'%d\'---\n", j, nodes->o_fd);
		j++;
		i = 0;
		while (nodes->options && nodes->options[i])
		{
			printf ("option[%d] = ---\"%s\"---\n", i, nodes->options[i]);
			i++;
		}
		printf ("type_i %d = --->%d<---\n", j, nodes->type_i);
		printf ("type_j %d = --->%d<---\n", j, nodes->type_o);
		nodes = nodes->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*cmdline;
	t_token		*lst;
	t_node		**kmi;
	char		*str;

	(void) ac;
	(void) av;
	str = NULL;
	kmi = take_env (env);
	cmdline = NULL;
	cmdline = malloc (sizeof(t_tokens));
	if (!cmdline)
		return (0);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(cmdline));
	cmdline->next = NULL;
	catch_sig();
	while (0 == 0)
	{
		// ft_exit_status(0);
		cmdline->input = readline("minishell-1$ ");
		if (!cmdline->input)
			exit(0); // TODO: add free and "exit\n" message in the STDOUT_FILENO;
		add_history(cmdline->input);
		cmdline = ft_lstnew(cmdline->input);
		lst = ft_lexer(cmdline->input);
		if (ft_check_syntax_error(lst))
			continue ;
		printf("tbon l3awda mnwd fawda\n");
		lst = ft_expand_and_quots(lst, *kmi);
		while (ft_join_if_need(lst))
			lst = ft_join_needed(lst);
		lst = ft_split_lst(lst);
		cmdline->options = ft_lst_to_tab(lst);
		ft_make_nodes(cmdline, lst);
		ft_heredoc(lst, cmdline);
		ft_in_file(cmdline, lst);
		ft_out_file(cmdline, lst);
		ft_debug(cmdline);
		if (cmdline->next && cmdline->next->input && cmdline->next->input[0])
		{
			if (build (cmdline->next->input) != 0)
				excut_biltins(build(cmdline->next->input), kmi, cmdline);
			else
				let_exec_command(find_path(get_node (kmi, "PATH")), \
									cmdline->next->options, make_list_arr(kmi));
		}
		else
			continue ;
	}
	return (0);
}
