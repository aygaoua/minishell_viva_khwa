/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_and_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 02:43:48 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 21:23:00 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excut_biltins(int cmd, t_node **my_list, t_tokens *cmdline)
{
	if (cmd == 1)
		ft_exit(cmdline->options + 1);
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

int	check_if_redirection(t_tokens *cmdline)
{
	if (cmdline->o_fd)
		return (1);
	return (0);
}

int	build(char *cmd)
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

void	redirections_in_more_cmds(t_node **my_list)
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

void exit_comd_not_found(char *cmd_path, char *cmd)
{
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
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
			matrix = ft_split(get_node(my_list, "PATH")->value_of_the_key, ':');
			cmd_path = get_cmd_path(matrix, list->options);
			exit_comd_not_found(cmd_path, list->options[0]);
			execve (cmd_path, list->options, env);
		}
		exit(EXIT_FAILURE);
	}
	else
		waitpid (pid, NULL, 0);
}
