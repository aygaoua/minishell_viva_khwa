/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_and_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 02:43:48 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 10:51:45 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    excut_biltins (int cmd, t_node **my_list, t_tokens *cmdline)
{
    if (cmd == 1)
        exit (0);
    else if (cmd == 2)
        my_pdw();
    else if (cmd == 3)
        my_echo_n (cmdline->options + 1);
    else if (cmd == 4)
        export_command (my_list, cmdline->options + 1);
    else if (cmd == 5)
        cd_command (my_list, cmdline->options + 1);
    else if (cmd == 6)
        unset_command (my_list, cmdline->options + 1);
    else if (cmd == 7)
        env_command (my_list);
}

int check_if_redirection(t_tokens *cmdline)
{
    if (cmdline->o_fd)
        return (1);
    return (0);
}

int	build (char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (2);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		return (3);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (4);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (5);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (6);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (7);
	else
		return (0);
}

void redirections_in_more_cmds(t_node **my_list)
{
	if ((*my_list)->cmd_in != STDIN_FILENO)
	{
		dup2 ((*my_list)->cmd_in, STDIN_FILENO);
		close ((*my_list)->cmd_in);
	}
	if ((*my_list)->cmd_out != STDOUT_FILENO)
	{
		dup2 ((*my_list)->cmd_out, STDOUT_FILENO);
		close ((*my_list)->cmd_out);
	}
}

void	cmd_in_pipe(t_tokens *list, t_node **my_list, char **env)
{
	pid_t	pid;
	char	**matrix;
	char	*cmd_path;

	pid = fork ();
	if (pid == -1)
		exit (EXIT_FAILURE);
	if (pid == 0)
	{
		redirections_in_more_cmds(my_list);
		if (build(list->options[0]))
			excut_biltins(build(list->options[0]), my_list, list);
		else
		{
			matrix = ft_split (get_node(my_list, "PATH")->value_of_the_key, ':');
			cmd_path = get_cmd_path(matrix, list->options);
			execve (cmd_path, list->options, env);
			perror("execve :");
			ft_free_matrix_contnt (matrix);
		}
		exit(EXIT_FAILURE);
	}
	else
		waitpid (pid, NULL, 0);
}

void set_command_io(t_node **my_list, int i_fd, int o_fd)
{
    if (i_fd == -2)
        (*my_list)->cmd_in = STDIN_FILENO;
    else
        (*my_list)->cmd_in = i_fd;
    if (o_fd == -2)
        (*my_list)->cmd_out = STDOUT_FILENO;
    else
        (*my_list)->cmd_out = o_fd;
}

void create_pipes(int pipes[][2], int size)
{
	int i = 0;
	while (i < size - 1)
	{
        pipe(pipes[i]);
		i++;
	}
}

void    bipa(t_tokens **list, t_node **my_list, char **env)
{
    t_tokens	*ptr;
	int			size;
	int			pipat[ft_lstsize_token((*list)) - 1][2];
	int			indx;

    ptr = (*list);
	size = ft_lstsize_token ((*list));
	indx = 0;
	create_pipes(pipat, size);
    while (ptr && indx < size)
    {
		set_command_io(my_list, ptr->i_fd, ptr->o_fd);
		if (indx == 0)
		{
			if ((*my_list)->cmd_out == STDOUT_FILENO)
				(*my_list)->cmd_out = pipat[indx][1];
			cmd_in_pipe (ptr, my_list, env);
			close ((*my_list)->cmd_out);
		}
		else if (indx > 0 && indx < size - 1)
		{
			if ((*my_list)->cmd_out == STDOUT_FILENO)
				(*my_list)->cmd_out = pipat[indx][1];
			if ((*my_list)->cmd_in == STDIN_FILENO)
			{
				close(pipat[indx - 1][1]);
				(*my_list)->cmd_in = pipat[indx - 1][0];
			}
			cmd_in_pipe (ptr, my_list, env);
			close ((*my_list)->cmd_in);
			close ((*my_list)->cmd_out);
		}
		else
		{
			if ((*my_list)->cmd_in == STDIN_FILENO)
			{
				close(pipat[indx - 1][1]);
				(*my_list)->cmd_in = pipat[indx - 1][0];
			}
			cmd_in_pipe (ptr, my_list, env);
			close ((*my_list)->cmd_in);
		}
		indx++;
		ptr = ptr->next;
    }
}
