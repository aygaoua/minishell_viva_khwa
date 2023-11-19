/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:14:35 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/19 00:08:50 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_expand_check(t_tokens **cmdline)
{
	int		i;
	int		k;
	int		j;
	char	**s;

	i = 0;
	k = 0;
	j = 0;
	s = malloc ((ft_elem_count((*cmdline)->cmd, '$') + 1) * 8);
	if (ft_elem_count((*cmdline)->cmd, '$'))
	{
		while ((*cmdline)->cmd[i] && j < ft_elem_count((*cmdline)->cmd, '$'))
			ft_expand_check_1(cmdline, &i, &s, &j);
		s[j] = NULL;
	}
	return (s);
}

void	ft_expand_check_1(t_tokens **cmdline, int *i, char ***s, int *j)
{
	int	k;

	k = 0;
	while ((*cmdline)->cmd[*i] != '$')
		(*i)++;
	(*i)++;
	k = (*i);
	while ((*cmdline)->cmd[k] != ' ' && (*cmdline)->cmd[k])
		k++;
	if (k != 0)
	{
		(*s)[*j] = malloc(k + 1);
		k = 0;
		while ((*cmdline)->cmd[*i] != ' ' && (*cmdline)->cmd[*i])
		{
			(*s)[*j][k] = (*cmdline)->cmd[*i];
			k++;
			(*i)++;
		}
		(*s)[*j][k] = '\0';
		printf("$----->%s\n", (*s)[*j]);
	}
	(*j)++;
}
