/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:39:13 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/30 10:50:12 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int				indx;
	unsigned char	*str1;
	unsigned char	*str2;

	if (!s1 || !s2)
		return (-2147483648);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	indx = 0;
	while (str1[indx] || str2[indx])
	{
		if (str1[indx] != str2[indx])
			return (str1[indx] - str2[indx]);
		indx++;
	}
	return (0);
}
