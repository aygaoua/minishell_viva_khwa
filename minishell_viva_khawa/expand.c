/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:14:35 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/27 02:56:46 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_check(t_tokens **cmdline, t_node **env_nds)
{
	int		i;
	int		k;
	int		j;
	t_node *env_nodes;

	env_nodes = *env_nds;
	i = 0;
	k = 0;
	j = 0;
	(*cmdline)->expand = malloc ((ft_elem_count((*cmdline)->cmd, '$') + 1) * 8);
	if (ft_elem_count((*cmdline)->cmd, '$'))
	{
		printf("-\n");
		while ((*cmdline)->cmd[i] && j < ft_elem_count((*cmdline)->cmd, '$'))
			ft_expand_check_1(cmdline, &i, &j);
		(*cmdline)->expand[j] = NULL;
	}
	else
		return ;
	i = 0;
	if ((*cmdline)->expand[i])
	{
		while ((*cmdline)->expand[i])
		{
			env_nodes = *env_nds;
			while (env_nodes)
			{
				if (ft_strcmp((*cmdline)->expand[i], env_nodes->key) == 0)
				{
					printf("Expanding ----> %s", (*cmdline)->expand[i]);
					free((*cmdline)->expand[i]);  // Free the old memory
					(*cmdline)->expand[i] = ft_strdup(env_nodes->value_of_the_key);
					printf(" to ----> %s\n", (*cmdline)->expand[i]);
					break;
				}
				env_nodes = env_nodes->next;
			}
			// if (env_nodes == NULL)
				
			i++;
		}
	}
}

void	ft_expand_check_1(t_tokens **cmdline, int *i, int *j)
{
	int	k;

	k = 0;
	while ((*cmdline)->cmd[*i] != '$')
		(*i)++;
	(*i)++;
	k = (*i) - k;
	while ((*cmdline)->cmd[k] != ' ' && (*cmdline)->cmd[k])
		k++;
	if (k != 0)
	{
		(*cmdline)->expand[*j] = malloc(k + 1);
		k = 0;
		while ((*cmdline)->cmd[*i] != ' ' && (*cmdline)->cmd[*i])
		{
			(*cmdline)->expand[*j][k] = (*cmdline)->cmd[*i];
			k++;
			(*i)++;
		}
		(*cmdline)->expand[*j][k] = '\0';
	}
	(*j)++;
}

