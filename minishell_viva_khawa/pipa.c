/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 04:31:31 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 22:50:11 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_token(t_tokens *lst)
{
	t_tokens	*j;
	int			i;

	if (!lst)
		return (0);
	j = lst;
	i = 0;
	while (j != NULL)
	{
		j = lst -> next;
		lst = j;
		i++;
	}
	return (i);
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

void	cmd_in_pipe(t_tokens *list, t_node **my_list, int i_fd, int o_fd)
{
	pid_t	pid;
	char	**matrix;
	char	**oth;
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
		cmd_path = get_path_cmand(matrix, list->options);
		if (!cmd_path)
			printf (" command not found: %s\n", list->options[0]);
		oth = make_list_arr (my_list);
		execve (cmd_path, list->options, oth);
		ft_free_matrix_contnt (matrix);
		exit(EXIT_FAILURE);
	}
	else
		waitpid (pid, NULL, 0);
}

void	bipa(t_tokens **list, t_node **my_list)
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
	while (ptr && indx < size)
	{
		if (indx == 0)
		{
			cmd_in_pipe (ptr, my_list, 0, pipat[indx][1]);
			close (pipat[indx][1]);
		}
		else if (indx > 0 && indx < size - 1)
		{
			cmd_in_pipe (ptr, my_list, pipat[indx - 1][0], pipat[indx][1]);
			close (pipat[indx - 1][0]);
			close (pipat[indx][1]);
		}
		else
		{
			cmd_in_pipe (ptr, my_list, pipat[indx - 1][0], 1);
			close (pipat[indx - 1][0]);
		}
		indx++;
		ptr = ptr->next;
	}
}
