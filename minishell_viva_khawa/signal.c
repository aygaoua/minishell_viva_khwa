/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 08:53:52 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 21:14:29 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_exit_status(1);
	}
}

void	catch_sig(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
