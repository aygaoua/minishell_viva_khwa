/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:38:28 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 23:42:48 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execut_builting_only(t_tokens *cmdline, t_node **kmi)
{
	int	i_tmp;
	int	o_tmp;

	if (cmdline->next->i_fd > 0)
	{
		i_tmp = dup(STDIN_FILENO);
		dup2(cmdline->next->i_fd, STDIN_FILENO);
		close(cmdline->next->i_fd);
	}
	if (cmdline->next->o_fd > 0)
	{
		o_tmp = dup(STDOUT_FILENO);
		dup2(cmdline->next->o_fd, STDOUT_FILENO);
		close(cmdline->next->o_fd);
	}
	excut_biltins(build(cmdline->next->input), kmi, cmdline);
	if (cmdline->next->i_fd > 0)
		dup2(i_tmp, STDIN_FILENO);
	if (cmdline->next->i_fd > 0)
		close(i_tmp);
	if (cmdline->next->o_fd > 0)
	{
		dup2(o_tmp, STDOUT_FILENO);
		close(o_tmp);
	}
}

void	ft_execute_moha(t_tokens *cmdline, t_node **kmi)
{
	char	**env;

	env = make_list_arr (kmi);
	if (ft_lstsize_token(cmdline) == 2)
	{
		if (build(cmdline->next->input) != 0)
			execut_builting_only(cmdline, kmi);
		else
			let_exec_command(find_path(get_node (kmi, "PATH")), \
								cmdline->options, env, &cmdline->next);
	}
	else if (ft_lstsize_token(cmdline) > 2)
		bipa(&cmdline->next, kmi, env);
}

void	execute_last_cmd(t_tokens *list, t_node **my_list, \
			char **env, int pipat[2])
{
	if ((*my_list)->cmd_in == STDIN_FILENO)
	{
		close(pipat[1]);
		(*my_list)->cmd_in = pipat[0];
	}
	cmd_in_pipe(list, my_list, env);
	close((*my_list)->cmd_in);
}
