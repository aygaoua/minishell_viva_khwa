/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:22:37 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/20 21:12:29 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	intial(t_node *new, char *str)
{
	new = ft_lstnew_k (str);
	if (is_equal (str) == 1)
		new->equl = 1;
}

void	export_command(t_node **my_env, char **arg)
{
	t_node	*new;
	int		row;

	row = -1;
	if (check_nil (my_env, arg) == 1)
		return ;
	while (arg[++row])
	{
		new = ft_lstnew_k (arg[row]);
		if (is_equal (arg[row]) == 1)
			new->equl = 1;
		if (how_alpha (new->key) == 0)
		{
			ft_free_contnue (&new);
			free (new);
			break ;
		}
		if (arg[row][0] == '=')
		{
			printf (" export: `%s': not a valid identifier\n", arg[row]);
			free (new);
			break ;
		}
		check_link (my_env, new);
	}
}
