/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:51:55 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/20 21:12:41 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*take_key_vlu(char *str)
{
	t_node	*new;

	new = ft_lstnew_k (str);
	return (new);
}

int	is_num_sp(char c)
{
	if ((c >= 33 && c <= 64) || (c >= 91 && c <= 94)
		|| c == 96 || (c >= 123 && c <= 126))
		return (1);
	return (0);
}

int	whitout_plus(char c)
{
	if (c == 43)
		return (2);
	if ((c >= 33 && c <= 42) || (c >= 44 && c <= 47) || (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 94) || c == 96 || (c >= 123 && c <= 126))
		return (1);
	return (0);
}

void	error_export(char *key, char *val)
{
	printf (" export: `%s", key);
	if (val)
		printf("=%s': not a valid identifier\n", val);
	else
		printf ("': not a valid identifier\n");
}

int	key_error(t_node *test)
{
	int	indx;

	indx = 0;
	if (is_num_sp (test->key[indx]) == 1)
	{
		error_export (test->key, test->value_of_the_key);
		return (1);
	}
	while (test->key[++indx])
	{
		if (whitout_plus(test->key[indx]) == 2)
		{
			if (test->key[indx + 1] != '\0')
			{
				error_export (test->key, test->value_of_the_key);
				return (1);
			}
		}
		else if (whitout_plus(test->key[indx]) == 1)
		{
			error_export (test->key, test->value_of_the_key);
			return (1);
		}
	}
	return (0);
}
