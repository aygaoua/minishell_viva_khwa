/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 04:46:27 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 13:33:27 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*p;

	i = 0;
	if(!s1)
		return NULL;
	len = ft_strlen(s1);
	p = (char *)malloc(len + 1);
	if (!p)
		return (0);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(p));
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
