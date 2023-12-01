/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:24:57 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 05:41:57 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execcmd_red(t_node **my_list, t_tokens **parss)
{
	char	**env;
	char	*slach;
	char	**path;
	// char	*ptr;
	char	*cmd_path;
	int		row;

	// ptr = NULL;
	row = 0;
	slach = add_slash ((*parss)->options[0]);
	path = find_path (get_node (my_list, "PATH"));

	pid_t pid;
	row = 0;
	while (path[row])
	{
		// if (ptr)
		// 	free (ptr);
		cmd_path = ft_strjoin (path[row], slach);
		// ptr = cmd_path;
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
	// ft_free_contnue (my_list);
	// ft_free_list (my_list);
	// ft_free_matrix_contnt (path);
	// free (slach);
	// free (ptr);
	return 0;
}
