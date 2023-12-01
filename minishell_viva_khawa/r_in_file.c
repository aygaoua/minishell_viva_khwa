/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_in_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:23:27 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 21:00:10 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_in_file(t_tokens *cmdline, t_token *lst)
{
	int	flag;

	flag = 1;
	if (cmdline->i_fd > 0)
		flag = 0;
	cmdline = cmdline->next;
	while (lst)
	{
		if (lst->type == R_IN)
		{
			if (cmdline->i_fd != -3)
				ft_open_in_file(lst->next->value, cmdline, flag);
		}
		if (lst->type == PIP)
		{
			cmdline = cmdline->next;
			flag = 1;
			if (cmdline && cmdline->i_fd > 0)
				flag = 0;
		}
		lst = lst->next;
	}
}

int	ft_open_in_file(char *s, t_tokens *cmdline, int flag)
{
	int	fd;

	if (cmdline->i_fd > 0)
		close(cmdline->i_fd);
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		ft_print_error(s);
		cmdline->i_fd = -3;
		// if (cmdline->options)
		// 	ft_free_matrix_contnt(cmdline->options);
		cmdline->options = NULL;
		ft_exit_status(1);
		return (1);
	}
	if (!flag)
		close(fd);
	else
		cmdline->i_fd = fd;
	return (0);
}
