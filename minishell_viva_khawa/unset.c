/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:04:50 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 21:00:32 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_only_one_node(t_node *node)
{
	free (node->key);
	free (node->value_of_the_key);
	free (node);
}

int	uneset_head(t_node **env, char *str)
{
	t_node	*ptr;
	t_node	*rm;

	ptr = (*env);
	if (ptr && ft_strcmp (ptr->key, str) == 0)
	{
		rm = ptr;
		(*env) = ptr->next;
		// ft_free_only_one_node (rm);
		return (0);
	}
	return (1);
}

int	empty_list(t_node **list)
{
	if (!(*list))
		return (1);
	return (0);
}

void	unset_key(t_node **env, char *str)
{
	t_node	*ptr;
	t_node	*rm;

	if (!env || !(*env))
		return ;
	ptr = (*env);
	while (ptr)
	{
		if (unset_error (str) == 1)
			break ;
		if (ptr->next && ft_strcmp (ptr->next->key, str) == 0)
		{
			rm = ptr->next;
			if (rm->next == NULL)
			{
				ptr->next = NULL;
				// ft_free_only_one_node (rm);
				break ;
			}
			ptr->next = ptr->next->next;
			// ft_free_only_one_node (rm);
		}
		ptr = ptr->next;
	}
}

void	unset_command(t_node **env, char **str)
{
	t_node	*ptr;
	int		row;

	row = 0;
	if (!env || !(*env))
		return ;
	while (str[row])
	{
		if (uneset_head(env, str[row]) == 0)
			ptr = (*env);
		else
		{
			ptr = (*env);
			unset_key (env, str[row]);
		}
		row++;
	}
}
