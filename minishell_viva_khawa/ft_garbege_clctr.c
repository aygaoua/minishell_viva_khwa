/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbege_clctr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:30:22 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 14:29:09 by azgaoua          ###   ########.fr       */
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