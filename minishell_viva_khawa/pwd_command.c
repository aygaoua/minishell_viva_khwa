/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:12:09 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/19 21:36:29 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_pdw(void)
{
	char	*buff;

	buff = getcwd (NULL, 0);
	printf ("%s\n", buff);
	free (buff);
}