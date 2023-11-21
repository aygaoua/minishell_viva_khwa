/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:51:52 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/21 00:00:09 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_node **list)
{
	t_node	*ptr;

	if (!list || !(*list))
		return ;
	ptr = (*list);
	while (ptr)
	{
		printf ("declare -x %s", ptr->key);
		if (ptr->value_of_the_key != NULL)
			printf ("=%c%s%c", 34, ptr->value_of_the_key, 34);
		printf ("\n");
		ptr = ptr->next;
	}
}

char	*ft_frontcpy_p(char *dst, char *src, char del)
{
	int	indx;

	indx = 0;
	if (!dst)
		dst = ft_calloc (ft_len (src, del) + 1, sizeof (char));
	while (src[indx] && src[indx] != del)
	{
		dst[indx] = src[indx];
		indx++;
	}
	dst[indx] = '\0';
	return (dst);
}

void	swap_nodes(t_node **my_env)
{
	t_node	*ptr;
	char	*swp0;
	char	*swp1;

	ptr = (*my_env);
	swp0 = NULL;
	swp1 = NULL;
	while (ptr)
	{
		if (ptr && ptr->next && ft_strcmp (ptr->key, ptr->next->key) > 0)
		{
			swp0 = ptr->key;
			swp1 = ptr->value_of_the_key;
			ptr->key = ptr->next->key;
			ptr->value_of_the_key = ptr->next->value_of_the_key;
			ptr->next->key = swp0;
			ptr->next->value_of_the_key = swp1;
			ptr = (*my_env);
		}
		else
			ptr = ptr->next;
	}
}

t_node	*check_is_exist(t_node **list, char *var)
{
	t_node	*ptr;

	ptr = (*list);
	while (ptr)
	{
		if (ft_strcmp (ptr->key, var) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	take_out(char *str)
{
	int	indx;

	indx = 0;
	while (str[indx])
	{
		if (str[indx] == '+')
		{
			str[indx] = '\0';
			return ;
		}
		indx++;
	}
}
