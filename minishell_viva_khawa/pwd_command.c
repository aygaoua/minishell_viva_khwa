/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:12:09 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/30 13:33:46 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_pdw(void)
{
	char	*buff;

	buff = getcwd (NULL, 0);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(buff));
	printf ("%s\n", buff);
}
