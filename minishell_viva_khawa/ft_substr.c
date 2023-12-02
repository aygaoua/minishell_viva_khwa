/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:34:58 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 13:32:57 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return ((void *)0);
	if (start >= ft_strlen(s))
		return (ft_strdup("\0"));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	p = malloc(len + 1);
	if (!p)
		return (0);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(p));
	i = 0;
	while (i < len)
	{
		p[i++] = s[start++];
		if (s[start - 1] != ' ' && s[start] == '\'')
			start++;
	}
	p[i] = '\0';
	return (p);
}
