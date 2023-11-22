/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:04:15 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/22 18:22:13 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	option(char *str)
{
	int	indx;

	if (str[0] != '-' || !str[1])
		return (1);
	indx = 1;
	while (str[indx])
	{
		if (str[indx] != 'n')
			return (1);
		indx++;
	}
	return (0);
}

int	delete_line(char **matrix, int row)
{
	while (matrix[row])
	{
		if (option (matrix[row]) == 1)
		{
			while (matrix[row])
			{
				printf ("%s", matrix[row]);
				if (matrix[row + 1])
					printf (" ");
				if (!matrix[row + 1])
					return (-1);
				row++;
			}
		}
		row++;
	}
	return (row);
}

int	with_new_line(char **darry, int row)
{
	while (darry[row])
	{
		printf ("%s", darry[row]);
		if (darry[row + 1])
			printf (" ");
		row++;
		if (!darry[row])
		{
			printf ("\n");
			return (-1);
		}
	}
	return (0);
}

void	my_echo_n(char **argum)
{
	int	row;

	if (!argum || !argum[0]) //aygaoua tester : echo '
		printf ("\n");
	row = 0;
	while (argum[row])
	{
		if (option (argum[row]) == 0)
		{
			row = delete_line (argum, row);
			if (row == -1)
				return ;
		}
		else
		{
			row = with_new_line (argum, row);
			if (row == -1)
				return ;
		}
		if (!argum[row])
			return ;
		row++;
	}
}
