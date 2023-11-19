/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:49:44 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/19 00:40:37 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_elem_count(char *s, char c)
{
	int	i;
	int	rtn;

	i = 0;
	rtn = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			rtn++;
		i++;
	}
	return (rtn);
}

int	ft_quots(t_tokens **cmdline)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_elem_count((*cmdline)->cmd, '"') \
		|| ft_elem_count((*cmdline)->cmd, '\''))
	{
		if (ft_elem_count((*cmdline)->cmd, '"') % 2 == 1 \
			|| ft_elem_count((*cmdline)->cmd, '\'') % 2 == 1)
			return (1);
		else
		{
			ft_s_quots((*cmdline)->input, &i);
			return (0);
		}
	}
	return (0);
}

char	**ft_s_quots(char *cmd, int *i)
{
	int		j;
	char	**s;

	j = 0;
	s = malloc((ft_elem_count(cmd, '\'') + 1) * 8);
	if (!s)
		return (NULL);
	if (ft_elem_count(cmd, '\''))
	{
		while (cmd[*i] && j < (ft_elem_count(cmd, '\'')) / 2)
		{
			while (cmd[*i] != '\'')
				(*i)++;
			ft_s_quots_1(&cmd, &s, &j, i);
			(*i)++;
			j++;
		}
		s[j] = NULL;
	}
	return (s);
}

void	ft_s_quots_1(char **cmd, char ***s, int *j, int *i)
{
	int	k;

	k = 0;
	if ((*cmd)[*i] == '\'')
	{
		(*i)++;
		if ((*cmd)[*i] == '\'')
			(*i)++;
		k = (*i);
		while ((*cmd)[k] != '\'' || !(*cmd)[k])
			k++;
		(*s)[*j] = malloc(k + 1);
		k = 0;
		while ((*cmd)[*i] != '\'' || !(*cmd)[*i])
		{
			(*s)[*j][k] = (*cmd)[*i];
			k++;
			(*i)++;
			if ((*cmd)[*i] == '\'' && (*cmd)[*i + 1] == '\'')
				(*i) += 2;
		}
		(*s)[*j][k] = '\0';
		printf("qouts == \"%s\"\n", (*s)[*j]);
	}
}
