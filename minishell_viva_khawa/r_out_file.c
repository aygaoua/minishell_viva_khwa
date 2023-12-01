/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_out_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:22:05 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 18:45:18 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_out_file(t_tokens *cmdline, t_token *lst)
{
	int	flag;

	flag = 1;
	if (cmdline->o_fd > 0)
		flag = 0;
	cmdline = cmdline->next;
	while (lst)
	{
		if (lst->type == R_OUT || lst->type == R_APPEND)
		{
			if (cmdline->o_fd != -3)
				ft_open_out_file(lst->next->value, cmdline, flag, lst->type); 
		}
		if (lst->type == PIP)
		{
			cmdline = cmdline->next;
			flag = 1;
			if (cmdline->o_fd > 0)
				flag = 0;
		}
		lst = lst->next;
	}
}

void	ft_print_error(char *s)
{
	write(2, "minishell-1$: ", 14);
	write(2, s, ft_strlen(s));
	write(2, ": ", 2);
	perror("");
}

void	ft_open_out_file(char *s, t_tokens *cmdline, int flag, int type)
{
	int	fd;

	if (cmdline->o_fd > 0)
		close(cmdline->o_fd);
	if (type == R_OUT)
	{
		cmdline->type_o = OUT_FILE;
		fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		cmdline->type_o = OUT_APPEND;
		fd = open(s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd < 0)
	{
		ft_print_error(s);
		cmdline->o_fd = -3;
		ft_exit_status(1);
		return ;
	}
	if (!flag)
		close(fd);
	else
		cmdline->o_fd = fd;
}
