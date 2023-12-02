/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:24:23 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 06:51:50 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_out_error(char *str)
{
	printf (" unset: `%s': not a valid identifier\n", str);
	ft_exit_status (1);
}

int	unset_error(char *test)
{
	int	indx;

	indx = 0;
	if (is_num_sp (test[indx]) == 1)
	{
		unset_out_error (test);
		return (1);
	}
	while (test[++indx])
	{
		if (whitout_plus(test[indx]) == 2)
		{
			if (test[indx + 1] != '\0')
			{
				unset_out_error (test);
				return (1);
			}
		}
		else if (whitout_plus(test[indx]) == 1)
		{
			unset_out_error (test);
			return (1);
		}
	}
	return (0);
}
