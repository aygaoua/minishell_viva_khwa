/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:18:14 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 12:13:26 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	j;

	if (!s)
		return ;
	j = 0;
	while (s[j])
	{
		ft_putchar_fd(s[j], fd);
		j++;
	}
}
