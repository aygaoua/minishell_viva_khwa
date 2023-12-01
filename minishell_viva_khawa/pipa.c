/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 04:31:31 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/02 00:17:47 by azgaoua          ###   ########.fr       */
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

void	execute_first_cmd(t_tokens *list, t_node **my_list, \
			char **env, int pipa)
{
	if ((*my_list)->cmd_out == STDOUT_FILENO)
		(*my_list)->cmd_out = pipa;
	cmd_in_pipe(list, my_list, env);
	close((*my_list)->cmd_out);
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
