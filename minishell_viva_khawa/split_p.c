/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:04:20 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/22 19:18:39 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_p(char const *s, unsigned int start, size_t len)
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
	i = 0;
	while (i < len)
	{
		if (s[start] == '\'')
            start++;
		p[i++] = s[start++];
	}
	p[i] = '\0';
	return (p);
}

static char	**freeme(char **s, size_t i)
{
	while (i >= 0 && s[i] != NULL)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

char	**ft_split_p(char *s, char c)
{
	size_t	i;
	size_t	j;
	char	**sp;

	i = 0;
	if (!s)
		return (NULL);
	sp = malloc(8 * lignes(s, c));
	if (!sp)
		return (0);
	while (*s)
	{
		j = 0;
		while (*s && *s == '\'')
			s++;
		while (*s && *s == c)
			s++;
		if (*s && *s == '\'')
		{
			s++;
			j++;
		}
		if (j != 0)
		{
            j = 0;
			while (s[j] && s[j] != '\'')
				j++;
		}
		if (j == 0)
		{
			while (s[j] && (s[j] != c))
				j++;
		}
		if (j != 0)
			sp[i++] = ft_substr_p(s, 0, j);
		if (j != 0 && !sp[i - 1])
			return (freeme(sp, i - 1));
        s += j;
        while (*s && *s == '\'')
			s++;
	}
	return (sp[i] = NULL, sp);
}
