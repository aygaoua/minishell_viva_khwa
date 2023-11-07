/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:48:55 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/04 16:20:14 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_tokens *lst)
{
	t_list	*j;
	int		i;

	if (!lst)
		return (0);
	j = lst;
	i = 0;
	while (j != NULL)
	{
		j = lst -> next;
		lst = j;
		i++;
	}
	return (i);
}
