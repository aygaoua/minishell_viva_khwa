/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_the_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:22:07 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/21 20:30:12 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **find_path(t_node *an_node)
{
    char    **paths;

    paths = ft_split (an_node->value_of_the_key, ':');
    return (paths);
}

char	*add_slash(char *str)
{
	int indx_i;
	int indx_j;
	int	len;
	char	*slash;

	indx_i = 0;
	indx_j = 0;
	len = ft_strlen (str) + 2;
	slash = ft_calloc (len, sizeof (char));
	if (!slash)
		return (NULL);
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

void    let_exec_command(char **path, char **command, char **envment)
{
	pid_t	pid;
	char	*slash;
	char	*cmd_path;
	int		row;

	if (!command || !command[0])
		return ;
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
			pid = fork ();
			if (pid == 0)
				execve (cmd_path, command, envment);
			wait(&pid);
		}
		row++;
	}
	free (cmd_path);
	ft_free_matrix_contnt (path);
	free (slash);
}
