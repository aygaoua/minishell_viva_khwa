/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_the_path1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:35:28 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 14:36:29 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirections_in_one_cmd(t_tokens **parss)
{
	if ((*parss)->i_fd != -2)
	{
		dup2((*parss)->i_fd, STDIN_FILENO);
		close((*parss)->i_fd);
	}
	if ((*parss)->o_fd != -2)
	{
		dup2((*parss)->o_fd, STDOUT_FILENO);
		close((*parss)->o_fd);
	}
}
