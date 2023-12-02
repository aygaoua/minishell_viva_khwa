/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_the_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:22:07 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/02 01:15:33 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_slash(char *str)
{
	int		indx_i;
	int		indx_j;
	int		len;
	char	*slash;

	indx_i = 0;
	indx_j = 0;
	len = ft_strlen (str) + 2;
	slash = ft_calloc (len, sizeof (char));
	if (!slash)
		return (NULL);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(slash));
	slash[indx_j] = '/';
	indx_j++;
	while (str[indx_i])
	{
		slash[indx_j] = str[indx_i];
		indx_i++;
		indx_j++;
	}
	return (slash);
}

int	how_many_row(char **arr)
{
	int	row;

	row = 0;
	while (arr[row])
		row++;
	return (row);
}

char	*get_cmd_path(char **path, char **command)
{
	char	*slash;
	char	*cmd_path;
	int		row;

	if (!command || !command[0] || !path || !path[0])
		return (NULL);
	row = 0;
	slash = add_slash (command[row]);
	cmd_path = NULL;
	while (path[row])
	{
		cmd_path = ft_strjoin (path[row], slash);
		if (access (cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		row++;
	}
	return (NULL);
}

void	clear_exec(pid_t pid, t_tokens **parss)
{
	int		status;

	if ((*parss)->i_fd > 0)
		close((*parss)->i_fd);
	if ((*parss)->o_fd > 0)
		close((*parss)->o_fd);
	waitpid(pid, &status, 0);
	ft_exit_status(status);
	exitstatus();
}

void	let_exec_command(char **path, char **command, \
			char **envment, t_tokens **parss)
{
	pid_t	pid;
	char	*cmd_path; 

	if (access(command[0], F_OK | X_OK) == 0)
		cmd_path = command[0];
	else
		cmd_path = get_cmd_path(path, command);
	if (!cmd_path && command[0])
		printf ("minishell-1$: %s: command not found\n", command[0]);
	pid = fork ();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redirections_in_one_cmd(parss);
		if (command[0])
			execve (cmd_path, command, envment);
		else
			exit(0);
		exit(127);
	}
	clear_exec(pid, parss);
}
