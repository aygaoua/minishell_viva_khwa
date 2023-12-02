/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_and_red2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:07:48 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 23:39:46 by azgaoua          ###   ########.fr       */
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

void	create_pipes(int **pipes, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		pipe(pipes[i]);
		i++;
	}
}

void	execute_middle_cmd(t_tokens *list, t_node **my_list, \
			char **env, t_var var)
{
	if ((*my_list)->cmd_out == STDOUT_FILENO)
		(*my_list)->cmd_out = var.tmpfd[1];
	if ((*my_list)->cmd_in == STDIN_FILENO)
	{
		close(var.pipa);
		(*my_list)->cmd_in = var.tmpfd[0];
	}
	cmd_in_pipe(list, my_list, env);
	close((*my_list)->cmd_in);
	close((*my_list)->cmd_out);
}

int	**allocate_pipes(int size)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc(sizeof(int *) * (size - 1));
	if (!pipes)
		return (NULL);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(pipes));
	while (i < size - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (NULL);
		i++;
	}
	return (pipes);
}

void	bipa(t_tokens **list, t_node **my_list, char **env)
{
	t_tokens		*ptr;
	int				**pipat;
	t_var			var;

	ptr = (*list);
	pipat = allocate_pipes(ft_lstsize_token((*list)));
	var.indx = 0;
	create_pipes(pipat, ft_lstsize_token((*list)));
	while (ptr)
	{
		set_command_io(my_list, ptr->i_fd, ptr->o_fd);
		if (var.indx == 0)
			execute_first_cmd(ptr, my_list, env, pipat[var.indx][1]);
		else if (var.indx > 0 && var.indx < ft_lstsize_token((*list)) - 1)
		{
			var.tmpfd[0] = pipat[var.indx - 1][0];
			var.tmpfd[1] = pipat[var.indx][1];
			var.pipa = pipat[var.indx - 1][1];
			execute_middle_cmd(ptr, my_list, env, var);
		}
		else
			execute_last_cmd(ptr, my_list, env, pipat[var.indx - 1]);
		var.indx++;
		ptr = ptr->next;
	}
}
