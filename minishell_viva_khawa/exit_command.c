/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:39:16 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 20:02:33 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(char *str)
{
	int	indx;

	indx = 0;
	while (str[indx])
	{
		if (str[indx] == '-' && indx == 0)
			indx++;
		if (ft_isdigit(str[indx]) == 0)
			return (1);
		indx++;
	}
	return (0);
}

static void	exit_status(size_t num)
{
	if (num >= 0 && num <= 256)
	{
		printf ("exiss|||t\n");
		ft_exit_status (num);
	}
	if (num > 256)
	{
		printf ("exidsdft\n");
				ft_exit_status (num % 256);
	}
}

static int	num_arg_of_exit(char *str)
{
	long long	arg;

	arg = ft_atoi (str);
	if (arg < 0 || arg > INT_MAX)
	{
		printf (" exit: %s: numeric argument required\n", str);
		ft_exit_status (arg);
		exit (arg);
		return (1);
	}
	exit_status (arg);
	return (0);
}

void	ft_exit(char **matrix)
{
	int			row;

	if (!matrix || !matrix[0])
	{
		ft_exit_status (0);
		printf ("exit\n");
		exit(0);
	}
	row = -1;
	while (matrix[++row])
	{
		if (is_word (matrix[row]) == 1)
		{
			printf ("excit\n");
			printf (" exit: %s: numeric argument required\n", matrix [row]);
			ft_exit_status (ft_atoi (matrix[row]));
			exit (ft_atoi (matrix[row]));
		}
		else
			num_arg_of_exit (matrix[row]);
	}
}
