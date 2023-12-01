/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:46:13 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 20:57:42 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**protect_env(void)
{
	char	**env;

	env = malloc(8 * 5);
	if (!env)
		return (NULL);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(env));
	env[0] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env[1] = ft_strdup(\
			"PWD=/Users/azgaoua/Desktop/my_minihell/minishell_viva_khawa");
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = NULL;
	return (env);
}

t_node	**take_env(char **env)
{
	t_node	**list;
	int		row;

	list = malloc (sizeof (t_node));
	if (!list)
		return (NULL);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(list));
	(*list) = NULL;
	if (!env)
		env = protect_env();
	row = 0;
	while (env[row] != NULL)
	{
		ft_lstadd_back_k (list, ft_lstnew_k (env[row]));
		row++;
	}
	return (list);
}

// t_node	**take_env(char **env)
// {
// 	t_node	**list;
// 	int		row;

// 	list = malloc (sizeof (t_node *));
// 	if (!list)
// 		return (NULL);
// 	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(list));
// 	(*list) = NULL;
// 	row = 0;
// 	while (env[row] != NULL)
// 	{
// 		ft_lstadd_back_k (list, ft_lstnew_k (env[row]));
// 		row++;
// 	}
// 	return (list);
// }

void	print_list(t_node **list)
{
	t_node	*ptr;

	if (!list)
		return ;
	ptr = (*list);
	while (ptr)
	{
		if (ptr->value_of_the_key)
			printf ("%s=%s\n", ptr->key, ptr->value_of_the_key);
		ptr = ptr->next;
	}
}

void	ft_free_contnue(t_node **lst)
{
	t_node	*ptr;

	if (!lst)
		return ;
	if (!(*lst))
		return ;
	ptr = (*lst);
	while (ptr)
	{
		// free (ptr->key);
		// free (ptr->value_of_the_key);
		ptr = ptr->next;
	}
}

void	ft_free_list(t_node **list)
{
	t_node	*ptr0;
	t_node	*ptr1;

	if (!list)
		return ;
	if (!(*list))
		return ;
	ptr0 = (*list);
	while (ptr0)
	{
		ptr1 = ptr0->next;
		ptr0 = ptr1;
	}
}
