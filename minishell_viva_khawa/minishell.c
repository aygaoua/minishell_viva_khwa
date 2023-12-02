/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:08:11 by azgaoua           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/02 00:25:45 by azgaoua          ###   ########.fr       */
=======
/*   Updated: 2023/11/30 00:29:15 by azgaoua          ###   ########.fr       */
>>>>>>> main
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
<<<<<<< HEAD
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
=======
	if (((*cmdline)->input[*i] && (*cmdline)->input[*i + 1] == '>') || \
		((*cmdline)->input[*i] && (*cmdline)->input[*i + 1] == '<') || \
		((*cmdline)->input[*i] == '<' && (*cmdline)->input[*i + 1] && \
		(*cmdline)->input[*i + 1] != '<') || \
		((*cmdline)->input[*i] == '>' && (*cmdline)->input[*i + 1] && \
		(*cmdline)->input[*i + 1] != '>') || (*cmdline)->input[*i] == '|')
	{
		(*j)++;
		(*s)[*j] = ' ';
	}
}

char	**ft_lst_to_tab(t_token *head)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc ((ft_lstsize(head) + 1) * 8);
	while (head)
	{
		if (head->type == R_APPEND || head->type == R_HERDOC \
			|| head->type == R_IN || head->type == R_OUT)
		{
			head = head->next;
			head = head->next;
		}
		else if (head->type == PIP)
			head = head->next;
		else
		{
			tab[i] = ft_strdup(head->value);
			head = head->next;
			i++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

// void ft_print_token(t_token *token)
// {
// 	while(token)
// 	{
// 		printf("%d [%s]\n", token->type, token->value);
// 		token = token->next;
// 	}
// }

int		ft_still_pip(t_token *lst)
{
	while (lst)
	{
		if (lst->type == PIP)
			return (1);
		lst = lst->next;
	}
	return (0);
}

t_token *ft_pips_pars(t_tokens *cmdline, t_token *lst)
{
	t_token *new_lst;
	char **tab;
	int i;
	int k = 0;

	new_lst = lst;
	i = 0;
	while (lst->type != PIP)
	{
		i++;
		lst = lst->next;
	}
	lst = new_lst;
	tab = malloc ((i + 1)* 8);
	while (k < i)
	{
		tab[k] = ft_strdup(lst->value);
		ft_lstadd_back2(&new_lst, ft_lstnew2(lst->value, lst->type));
		lst = lst->next;
		k++;
	}
	lst = lst->next;
	tab[k] = NULL;
	cmdline->options = tab;
	return (new_lst);
}

int ft_heredoc_on(t_token *lst)
{
	while (lst)
	{
		if (lst->type == R_HERDOC)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	ft_open_herdoc(char *s, t_tokens *cmdline)
{
	char	*str;
	int fd[2];

	if (pipe(fd) == -1)
	{
		perror("pip");
		return ;
	}
	if (cmdline->i_fd > 0)
		close(cmdline->i_fd);
	cmdline->i_fd = fd[1];
	while(0 == 0)
	{
		str = readline(">");
		if (ft_strcmp(s, str) == 0)
		{
			close(fd[1]);
			cmdline->i_fd = fd[0];
			break ;
		}
		write(cmdline->i_fd, str, ft_strlen(str));
		write(cmdline->i_fd, "\n", 1);
	}
}

int	ft_open_in_file(char *s, t_tokens *cmdline, int flag)
{
	int fd;
	if (cmdline->i_fd > 0)
		close(cmdline->i_fd);
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		write(2, "minishell-1$: ", 14);
		write(2, s, ft_strlen(s));
		write(2, ": ", 2);
		perror("");
		cmdline->i_fd = -3;
		if (cmdline->options)
			ft_free_matrix_contnt(cmdline->options);
		cmdline->options = NULL;
		return (1);
	}
	if (!flag)
		close(fd);
	else
		cmdline->i_fd = fd;
	return (0);
}

void	ft_heredoc(t_token *lst, t_tokens *cmdline)
{
	cmdline = cmdline->next;
	while (lst)
	{
		if (lst->type == R_HERDOC)
			ft_open_herdoc(lst->next->value, cmdline);
		if (lst->type == PIP)
			cmdline = cmdline->next;
		lst = lst->next;
	}
}

void	ft_in_file(t_tokens *cmdline, t_token *lst)
{
	int flag;

	flag = 1;
	if (cmdline->i_fd > 0)
		flag = 0;
	cmdline = cmdline->next;
	while (lst)
	{
		if (lst->type == R_IN)
		{
			if (cmdline->i_fd != -3)
				ft_open_in_file(lst->next->value, cmdline, flag);
		}
		if (lst->type == PIP)
		{
			cmdline = cmdline->next;
			flag = 1;
			if (cmdline->i_fd > 0)
				flag = 0;
		}
		lst = lst->next;
	}
}

void	ft_make_nodes(t_tokens *cmdline, t_token *lst)
{
	int	i;
	int	j;
	t_token		*head;

	while (lst)
	{
		head = lst;
		j = 0;
		i = 0;
		ft_lstadd_back(&cmdline, ft_lstnew(lst->value));
		cmdline = cmdline->next;
		if (lst->type == PIP)
			lst = lst->next;
		while (lst && lst->type != PIP)// you forget the protection
		{
			if (lst->type != R_APPEND && lst->type != R_HERDOC \
				&& lst->type != R_IN && lst->type != R_OUT)
				i++;
			else
				lst = lst->next;
			lst = lst->next;
		}
		cmdline->options = malloc((i + 1) * 8);
		lst = head;
		while (lst && lst->type != PIP)
		{
			if (lst->type != R_APPEND && lst->type != R_HERDOC \
				&& lst->type != R_IN && lst->type != R_OUT)
			{
				cmdline->options[j] = ft_strdup(lst->value);
				j++;
			}
			else
				lst = lst->next;
			lst = lst->next;
		}
		cmdline->options[j] = NULL;
		if (lst)
			lst = lst->next;
	}
}

void ft_open_out_file(char *s, t_tokens *cmdline, int flag, int type)
{
	int fd;

	if (cmdline->o_fd > 0)
		close(cmdline->o_fd);
	if (type == R_OUT)
	{
		cmdline->type_o = OUT_FILE;
		fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		cmdline->type_o = OUT_APPEND;
		fd = open(s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd < 0)
	{
		write(2, "minishell-1$: ", 14);
		write(2, s, ft_strlen(s));
		write(2, ": ", 2);
		perror("");
		cmdline->o_fd = -3;
		if (cmdline->options)
			ft_free_matrix_contnt(cmdline->options);
		cmdline->options = NULL;
		return ;
	}
	if (!flag)
		close(fd);
	else
		cmdline->o_fd = fd;
}


void ft_out_file(t_tokens *cmdline, t_token *lst)
{
	int flag;

	flag = 1;
	if (cmdline->o_fd > 0)
		flag = 0;
	cmdline = cmdline->next;
	while (lst)
	{
		if (lst->type == R_OUT || lst->type == R_APPEND)
		{
			if (cmdline->o_fd != -3)
				ft_open_out_file(lst->next->value, cmdline, flag, lst->type); 
		}
		if (lst->type == PIP)
		{
			cmdline = cmdline->next;
			flag = 1;
			if (cmdline->o_fd > 0)
				flag = 0;
		}
		lst = lst->next;
	}
>>>>>>> main
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
<<<<<<< HEAD
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
=======
	cmdline->next = NULL;// added bye hamza plus ; what are you doing in this part ? no propre initialization
	while (0 == 0)
	{
		cmdline->input = readline("minishell-1$ ");
		add_history(cmdline->input);
		cmdline = ft_lstnew(cmdline->input);
		lst = ft_lexer(cmdline->input);
		if (cmdline->input && cmdline->input[0])
		{
			lst = ft_expand_and_quots(lst, *kmi);
			if (ft_check_syntax_error(lst))
				printf("syntaks a m3allem\n");
			while (ft_join_if_need(lst))
				lst = ft_join_needed(lst);
			lst = ft_split_lst(lst);
			cmdline->options = ft_lst_to_tab(lst);
			ft_make_nodes(cmdline, lst);
			ft_heredoc(lst, cmdline);
			ft_in_file(cmdline, lst);
			ft_out_file(cmdline, lst);
			ft_debug(cmdline);
			// ft_print_token(lst);
			// while (ft_still_pip(lst))
			// 	lst = ft_pips_pars(cmdline, lst);
			// cmdline = ft_pip_split(cmdline, lst);
			// cmdline->i_fd = ft_get_in_file();
			// cmdline->cmd = ft_convert_line(&cmdline);
			// ft_expand_check(&cmdline, kmi);
			// ft_get_real_args(&cmdline, *kmi);
			// cmdline = ft_lstnew(cmdline->cmd);
			if (ft_strncmp(cmdline->input, "exit", 5) == 0)
				exit(0);
			else if (ft_strncmp(cmdline->input, "echo", 4) == 0)
				my_echo_n((cmdline->options + 1));
			else if (ft_strncmp(cmdline->input, "cd", 2) == 0)
				cd_command (take_env (env), cmdline->options + 1);
			else if (ft_strncmp(cmdline->input, "pwd", 3) == 0)
				my_pdw();
/*#######################this is mo7a O 7madd speaking########################*/
			else if (ft_strncmp(cmdline->input, "export", 6) == 0)
			{
				// t_node **kmi = take_env (env);
				printf ("THIS IS EXPORT%p\n",cmdline->options + 2);
				export_command (kmi, cmdline->options + 1);
				// export_command (take_env (env), NULL);
				print_export (kmi);
			}
			else if (ft_strncmp(cmdline->input, "unset", 5) == 0)
			{
				printf ("THIS IS UNSET\n");
				unset_command (kmi, cmdline->options + 1);
				// if (kmi)
					print_export (kmi);
			}
			else if (ft_strncmp(cmdline->input, "env", 3) == 0)
			{
				printf ("THIS IS ENV\n");
				env_command(env);
			}
			else
				let_exec_command (find_path (get_node (kmi , "PATH")), cmdline->options, make_list_arr (kmi));
/*#######################this is mo7a O 7madd speaking########################*/
		}
		else
>>>>>>> main
			continue ;
		if (cmdline->next && cmdline->next->input && cmdline->next->input[0])
			ft_execute_moha(cmdline, kmi);
	}
	return (0);
}
