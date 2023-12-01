/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_and_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 02:43:48 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 06:51:33 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excut_biltins (int cmd, t_node **my_list, t_tokens *cmdline)
{
	if (cmd == 1)
		exit (0);
	else if (cmd == 2)
		my_pdw ();
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

int	check_if_redirection(t_tokens *cmdline)
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

int	execcmd_red(t_node **my_list, t_tokens **parss)
{
	pid_t pid;
	char *slach;
	char **path;
	char **env;
	char *cmd_path = NULL;
	int row = 0;

	slach = add_slash ((*parss)->options[0]);
	path = find_path (get_node (my_list, "PATH"));
	env = make_list_arr (my_list);
	row = 0;
	while (path[row])
	{
		cmd_path = ft_strjoin (path[row], slach);
		if (access (cmd_path, F_OK) == 0)
		{
			pid = fork ();
			if (pid	== 0)
			{
				if ((*parss)->i_fd != -2)
				{
					dup2((*parss)->i_fd, STDIN_FILENO);
					close((*parss)->i_fd);
				}
				if ((*parss)->o_fd != -2 )
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
	return 0;
}

char	*get_path_cmand(char **path, char **command)
{
	char	*slash;
	char	*cmd_path;
	int		row;

	row = 0;
	slash = add_slash (command[row]);
	cmd_path = NULL;
	while (path[row])
	{
		if (cmd_path)
			free (cmd_path);
		cmd_path = ft_strjoin (path[row], slash);
		if (access (cmd_path, F_OK) == 0)
		{
			return (cmd_path);
		}
		row++;
	}
	free (cmd_path);
	ft_free_matrix_contnt (path);
	free (slash);
	return (NULL);
}

void	cmd_in_pipe(t_tokens *list, t_node **my_list, int i_fd, int o_fd, char **env)
{
	pid_t	pid;
	char	**matrix;
	char	*cmd_path;

	pid = fork ();
	if (pid == -1)
	{
		perror ("fork");
		exit (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (i_fd != STDIN_FILENO)
		{
			dup2 (i_fd, STDIN_FILENO);
			close (i_fd);
		}
		if (o_fd != STDOUT_FILENO)
		{
			dup2 (o_fd, STDOUT_FILENO);
			close (o_fd);
		}
		matrix = ft_split (get_node (my_list, "PATH")->value_of_the_key, ':');
		cmd_path = get_path_cmand(matrix,list->options);
		if (!cmd_path)
			printf (" command not found: %s\n", list->options[0]);
		execve (cmd_path, list->options, env);
		ft_free_matrix_contnt (matrix);
		exit(EXIT_FAILURE);
	}
	else
		waitpid (pid, NULL, 0);
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
	while (indx < size -1)
	{
		pipe(pipat[indx]);
		indx++;
	}
	indx = 0;
	if ((*list)->i_fd == -2)
		(*list)->i_fd = STDIN_FILENO;
	if ((*list)->o_fd == -2)
		(*list)->o_fd =STDOUT_FILENO;
	while (ptr && indx < size)
	{
		if (indx == 0)
		{
			if (ptr->o_fd == STDOUT_FILENO)
				ptr->o_fd = pipat[indx][1];
			cmd_in_pipe (ptr, my_list, 0, pipat[indx][1], env);
			close (pipat[indx][1]);
		}
		else if (indx > 0 && indx < size - 1)
		{
			if (ptr->o_fd == STDOUT_FILENO)
				ptr->o_fd = pipat[indx][1];
			if (ptr->i_fd == STDIN_FILENO)
				ptr->i_fd = pipat[indx - 1][0];
			cmd_in_pipe (ptr, my_list,pipat[indx - 1][0], pipat[indx][1], env);
			close (pipat[indx - 1][0]);
			close (pipat[indx][1]);
		}
		else
		{
			if (ptr->i_fd == STDIN_FILENO)
				ptr->i_fd = pipat[indx - 1][0];
			cmd_in_pipe (ptr,my_list, pipat[indx - 1][0], 1, env);
			close (pipat[indx - 1][0]);
		}
		indx++;
		ptr = ptr->next;
	}
}