/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_and_red2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:07:48 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 14:12:24 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_command_io(t_node **my_list, int i_fd, int o_fd)
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

void	create_pipes(int pipes[][2], int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		pipe(pipes[i]);
		i++;
	}
}

//---------------->>Variable length array forbidden !!NORMINETTE!!
void	bipa(t_tokens **list, t_node **my_list, char **env)
{
	t_tokens	*ptr;
	int			indx;
	int			size;
	int			pipat[ft_lstsize_token((*list)) - 1][2];

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
