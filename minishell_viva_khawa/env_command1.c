/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:20:54 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/19 18:02:00 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

int	is_ther_the_win_char(char *str, char c, int len)
{
	int	indx;

	indx = 0;
	while (indx < len && str[indx])
	{
		if (str[indx] == c)
			return (1);
		indx++;
	}
	return (0);
}

char	*ft_frontcpy(char *dst, char *src, char del)
{
	int	indx;

	if (!src)
		return (NULL);
	indx = 0;
	if (!dst)
		dst = ft_calloc (ft_len (src, del) + 1, sizeof (char));
	if (!dst)
		return (NULL);
	while (src[indx] && src[indx] != del)
	{
		dst[indx] = src[indx];
		indx++;
	}
	dst[indx] = '\0';
	return (dst);
}

char	*ft_backcpy(char *dst, char *src, char del)
{
	int	indx;
	int	indj;
	int	len;

	if (!src)
		return (NULL);
	if (is_ther_the_win_char(src, del, ft_strlen (src)) == 0)
		return (NULL);
	indx = 0;
	indj = 0;
	len = ft_strlen (src) - ft_len (src, del);
	if (!dst)
		dst = ft_calloc (len + 1, sizeof (char));
	while (src[indx] && src[indx] != del)
		indx++;
	if (src[indx] == del)
	{
		indx++;
		while (src[indx])
			dst[indj++] = src[indx++];
		dst[indj] = '\0';
	}
	return (dst);
}
