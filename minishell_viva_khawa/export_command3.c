/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:51:57 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 22:55:24 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_alpha(char *str)
{
	int	indx;
	int	cont;

	indx = 0;
	cont = 0;
	while (str[indx])
	{
		if (str[indx] == 95 && str[indx + 1] != '\0')
			cont++;
		if (ft_isalpha (str[indx]) == 1 || ft_isdigit (str[indx]) == 1)
			cont++;
		indx++;
	}
	return (cont);
}

int	is_ther_plus(char *str)
{
	int	indx;

	indx = 0;
	while (str[indx])
	{
		if (str[indx] == '+')
			return (1);
		indx++;
	}
	return (0);
}

void	make_out(t_node *node)
{
	node->plus = 1;
	take_out (node->key);
}

int	is_equal(char *str)
{
	int	indx;

	indx = 0;
	while (str[indx])
	{
		if (str[indx] == '=')
			return (1);
		indx++;
	}
	return (0);
}

void	export_remplass(t_node *list, t_node *one)
{
	char	*ptr;

	ptr = list->value_of_the_key;
	list->value_of_the_key = one->value_of_the_key;
}
