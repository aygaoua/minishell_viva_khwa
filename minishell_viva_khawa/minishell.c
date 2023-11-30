/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:08:11 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 16:44:54 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_collector	**ft_collector(void)
{
	static t_collector *colctr;
	return (&colctr);
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
		if (head->type == R_APPEND || head->type == R_HERDOC \
			|| head->type == R_IN || head->type == R_OUT)
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
	return (tab[i] = NULL ,tab);
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
			if (cmdline && cmdline->i_fd > 0)
				flag = 0;
		}
		lst = lst->next;
	}
}

int execcmd_red(t_node **my_list, t_tokens **parss)
{
	char **env = make_list_arr (my_list);
	char *slach;
	char **path;
	char *ptr = NULL;
	char *cmd_path = NULL;
	int row = 0;

	slach = add_slash ((*parss)->options[0]);
	path = find_path (get_node (my_list, "PATH"));

	pid_t pid;
	row = 0;
	while (path[row])
	{
		if (ptr)
			free (ptr);
		cmd_path = ft_strjoin (path[row], slach);
		ptr = cmd_path;
		if (access (cmd_path, F_OK) == 0)
		{
			pid = fork ();
			if (pid    == 0)
			{
				if ((*parss)->i_fd > 0)
				{
					dup2((*parss)->i_fd, STDIN_FILENO);
					close((*parss)->i_fd);
				}
				if ((*parss)->o_fd > 0)
				{
					dup2((*parss)->o_fd, STDOUT_FILENO);
					close((*parss)->o_fd);
				}
				execve(cmd_path, (*parss)->options, env);
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		row++;
	}
	waitpid(pid, NULL, 0);
	ft_free_contnue (my_list);
	ft_free_list (my_list);
	ft_free_matrix_contnt (path);
	free (slach);
	free (ptr);
	return 0;
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
		while (lst && lst->type != PIP)
		{
			if (lst->type != R_APPEND && lst->type != R_HERDOC \
				&& lst->type != R_IN && lst->type != R_OUT)
				i++;
			else
				lst = lst->next;
			if (lst)
				lst = lst->next;
		}
		cmdline->options = malloc((i + 1) * 8);
		if (!cmdline->options)
			return ;
		ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(cmdline->options));
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
			if (lst)
				lst = lst->next;
		}
		cmdline->options[j] = NULL;
		if (lst)
			lst = lst->next;
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
	(void) ac;
	(void) av;
	t_tokens	*cmdline;
	t_token 	*lst;
	t_node **kmi = take_env (env);/*this is mo7a O 7madd speaking*/
	char		*str;

	str = NULL;
	cmdline = NULL;
	cmdline = malloc (sizeof(t_tokens));
	if (!cmdline)
		return (0);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(cmdline));
	// cmdline->next = NULL;// added bye hamza plus ; what are you doing in this part ? no propre initialization
	while (0 == 0)
	{
		cmdline->input = readline("minishell-1$ ");
		add_history(cmdline->input);
		cmdline = ft_lstnew(cmdline->input);
		lst = ft_lexer(cmdline->input);
		lst = ft_expand_and_quots(lst, *kmi);
		if (ft_check_syntax_error(lst))
			continue ;
		while (ft_join_if_need(lst))
			lst = ft_join_needed(lst);
		lst = ft_split_lst(lst);
		cmdline->options = ft_lst_to_tab(lst);
		ft_make_nodes(cmdline, lst);
		ft_heredoc(lst, cmdline);
		ft_in_file(cmdline, lst);
		ft_out_file(cmdline, lst);
		ft_debug(cmdline);
		if (cmdline->input && cmdline->input[0])
		{
			if (ft_strncmp(cmdline->input, "exit", 5) == 0)
				break ;
			else if (ft_strncmp(cmdline->input, "echo", 4) == 0)
				my_echo_n((cmdline->options + 1));
			else if (ft_strncmp(cmdline->input, "cd", 2) == 0)
				cd_command (take_env (env), cmdline->options + 1);
			else if (ft_strncmp(cmdline->input, "pwd", 3) == 0)
				my_pdw();
			else if (ft_strncmp(cmdline->input, "export", 6) == 0)
			{
				printf ("THIS IS EXPORT%p\n",cmdline->options + 2);
				export_command (kmi, cmdline->options + 1);
				print_export (kmi);
			}
			else if (ft_strncmp(cmdline->input, "unset", 5) == 0)
			{
				printf ("THIS IS UNSET\n");
				unset_command (kmi, cmdline->options + 1);
				print_export (kmi);
			}
			else if (ft_strncmp(cmdline->input, "env", 3) == 0)
			{
				printf ("THIS IS ENV\n");
				env_command(env);
			}
			else
				let_exec_command (find_path (get_node (kmi , "PATH")), cmdline->options, make_list_arr (kmi));
			// atexit(vv);
		}
		else
			continue ;
	}
	// ft_free_clctr(ft_collector());
	return (0);
}
