/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:52:00 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/20 21:12:55 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remplace(t_node *list, t_node *one)
{
	if (one->equl == 1 && one->plus == 0)
		export_remplass (list, one);
	else
	{
		ft_free_contnue (&one);
		free (one);
	}
}

void	export_conca(t_node *list, t_node *one)
{
	char	*ptr;

	ptr = list->value_of_the_key;
	list->value_of_the_key = ft_strjoin
		(list->value_of_the_key, one->value_of_the_key);
	free (ptr);
	ft_free_contnue (&one);
	free (one);
}

void	take_last_link(t_node **env, t_node *new)
{
	t_node	*last;

	last = ft_lstlast_k (env);
	last->next = new;
}

void	check_link(t_node **my_env, t_node *new)
{
	t_node	*an_node;

	if (!my_env || !new)
		return ;
	if (key_error (new) == 0)
	{
		if (is_ther_plus (new->key) == 1)
			make_out (new);
		an_node = check_is_exist (my_env, new->key);
		if (an_node != NULL)
		{
			if (new->plus == 1)
				export_conca (an_node, new);
			else
				remplace (an_node, new);
		}
		else
			take_last_link(my_env, new);
	}
	else
	{
		ft_free_contnue (&new);
		free (new);
	}
}

int	check_nil(t_node **env, char **matrix)
{
	if (!matrix)
	{
		swap_nodes (env);
		print_export (env);
		return (1);
	}
	return (0);
}
