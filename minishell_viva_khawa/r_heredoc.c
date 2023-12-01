/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:25:26 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 20:59:57 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_token *lst, t_tokens *cmdline)
{
	cmdline = cmdline->next;
	while (lst)
	{
		if (lst->next && lst->type == R_HERDOC)
			ft_open_herdoc(lst->next->value, cmdline);
		if (lst->type == PIP)
			cmdline = cmdline->next;
		lst = lst->next;
	}
}

void	ft_handle_error( void )
{
	ft_exit_status(1);
	perror("pip");
}
void	ft_open_herdoc(char *s, t_tokens *cmdline)
{
	char	*str;
	int		fd[2];

	if (pipe(fd) == -1)
		return (ft_handle_error());
	if (cmdline->i_fd > 0)
		close(cmdline->i_fd);
	cmdline->i_fd = fd[1];
	while (0 == 0)
	{
		str = readline(">");
		if (ft_strcmp(s, str) == 0)
		{
			close(fd[1]);
			cmdline->i_fd = fd[0];
			break ;
		}
		write(cmdline->i_fd, str, ft_strlen(str));
		write(cmdline->i_fd, "\n", 1);
		// free(str);
	}
	// if (str)
	// 	free(str);
}
