/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:14:35 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/25 22:02:04 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_expand_check(t_tokens **cmdline, t_node **env_nodes)
{
	int		i;
	int		k;
	int		j;
	char	**s;
	t_node *env_head;

	env_head = *env_nodes;
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
	else
		return (NULL);
	i = 0;
	if (s[i])
	{
		while (s[i])
		{
			while ((*env_nodes))
			{
				if (ft_strcmp(s[i], (*env_nodes)->key) == 0)
				{
					printf("expanding ----> %s", s[i]);
					s[i] = (*env_nodes)->value_of_the_key;
					printf(" to ----> %s\n", s[i]);
					*env_nodes = env_head;
					break;
				}
				else
					(*env_nodes) = (*env_nodes)->next;
			}
			i++;
		}
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
		// printf("$----->%s\n", (*s)[*j]);
	}
	(*j)++;
}
