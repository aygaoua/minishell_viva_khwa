/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:01:31 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/02 01:15:46 by azgaoua          ###   ########.fr       */
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
	if (s[0] == '?')
		return (1);
	while (s[j] && (s[j] == '_' || ft_isalpha(s[j]) \
			|| ft_isdigit(s[j])))
		j++;
	return (j);
}

void	ft_quote_hand(int *q, int type, char **inside, t_token **lst)
{
	if (*q == 0)
		*q = type;
	else if (*q == type)
	{
		*q = 0;
		ft_lstadd_back2(lst, ft_lstnew2(*inside, WORD));
		*inside = NULL;
	}
}

char	**find_path(t_node *an_node)
{
	char	**paths;

	if (!an_node || !an_node->value_of_the_key)
		return (NULL);
	paths = ft_split (an_node->value_of_the_key, ':');
	return (paths);
}
