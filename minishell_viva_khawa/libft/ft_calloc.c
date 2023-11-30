/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 03:58:48 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 13:34:09 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*i;

	i = malloc(count * size);
	if (i)
	{
		ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(i));
		ft_bzero(i, count * size);
		return (i);
	}
	return (0);
}
