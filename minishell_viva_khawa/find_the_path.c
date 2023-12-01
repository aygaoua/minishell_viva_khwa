/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_the_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:22:07 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 13:04:52 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_path(t_node *an_node)
{
	char	**paths;

	if (!an_node || !an_node->value_of_the_key)
		return (NULL);
	paths = ft_split (an_node->value_of_the_key, ':');
	return (paths);
}

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

int    how_many_row(char **arr)
{
    int    row;

    row = 0;
    while (arr[row])
        row++;
    return (row);
}

char *get_cmd_path(char **path, char **command)
{
    char    *slash;
    char    *cmd_path;
    int        row;

    if (!command || !command[0] || !path || !path[0])
        return NULL;
    row = 0;
    slash = add_slash (command[row]);
    cmd_path = NULL;
    while (path[row])
    {
        if (cmd_path)
            free (cmd_path);
        cmd_path = ft_strjoin (path[row], slash);
        if (access (cmd_path, F_OK | X_OK) == 0)
        {
            ft_free_matrix_contnt (path);
            free (slash);
            return (cmd_path);
        }
        row++;
    }        
    ft_free_matrix_contnt (path);
    free (slash);
    return (NULL);
}

void    let_exec_command(char **path, char **command, char **envment)
{
    pid_t    pid;
	int		status;
    char *cmd_path; 
    
    if (access(command[0], F_OK | X_OK) == 0)
        cmd_path = command[0];
    else
        cmd_path = get_cmd_path(path, command);
    if (!cmd_path)
	{
        printf ("minishell %s: command not found\n", command[0]);
		ft_exit_status(127);
	}
    pid = fork ();
    if (pid == 0)
    {
        execve (cmd_path, command, envment);
        exit(127);
    }
    waitpid(pid, &status, 0);
	ft_exit_status(status);
    free (cmd_path);
}

void redirections_in_one_cmd(t_tokens **parss)
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
}
