/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmmand1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:13:29 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 06:41:37 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*get_node(t_node **list, char *str)
{
	t_node	*ptr;

	if (!list || !(*list))
		return (NULL);
	ptr = (*list);
	while (ptr)
	{
		if (ft_strcmp (ptr->key, str) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int	arg_path(char *str)
{
	if (str[0] != '-' && str[0] != '~')
		return (0);
	return (-1);
}

void	print_oldpwd(t_node **my_env)
{
	t_node	*ptr;

	if (!my_env || !(*my_env))
		return ;
	ptr = (*my_env);
	while (ptr)
	{
		if (ptr && ft_strcmp (ptr->key, "OLDPWD") == 0)
		{
			printf ("%s\n", ptr->value_of_the_key);
			return ;
		}
		ptr = ptr->next;
	}
}
