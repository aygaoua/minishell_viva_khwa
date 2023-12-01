/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbege_clctr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:30:22 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 22:52:49 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_collector	**ft_collector(void)
{
	static t_collector	*colctr;

	return (&colctr);
}

int	ft_exit_status(int status)
{
	static int	exit_status;

	if (status != -1)
		exit_status = status;
	return (exit_status);
}

void	signal_name(int signal)
{
	if (signal == 3)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	if (signal == 6)
		ft_putstr_fd("Aborted\n", STDERR_FILENO);
	if (signal == 7)
		ft_putstr_fd("Bus error\n", STDERR_FILENO);
	if (signal == 11)
		ft_putstr_fd("Segmentation fault: 11\n", STDERR_FILENO);
	if (signal == 15)
		ft_putstr_fd("Terminated\n", STDERR_FILENO);
}

void	exitstatus(void)
{
	int		signal;
	int		exit_status;

	exit_status = ft_exit_status(-1);
	if (WIFEXITED(exit_status))
		ft_exit_status(WEXITSTATUS(exit_status));
	else if (WIFSIGNALED(exit_status))
	{
		signal = WTERMSIG(exit_status);
		ft_exit_status(signal + 128);
		signal_name(signal);
	}
}
