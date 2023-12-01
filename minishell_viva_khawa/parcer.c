/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:01:31 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 23:02:16 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_to_search(t_token *lst)
{
	int	i;

	i = 0;
	if (lst && (lst->type == WORD \
		&& (lst->value[0] == '_' || ft_isalpha(lst->value[0]))))
		return (1);
	return (0);
}

int	ft_len_var(char *s)
{
	int	j;

	j = 0;
	while (s[j] && (s[j] == '_' || ft_isalpha(s[j]) \
			|| ft_isdigit(s[j])))
		j++;
	return (j);
}
