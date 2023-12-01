/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:39:13 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 15:05:19 by azgaoua          ###   ########.fr       */
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

char	*ft_get_env(char *lst_key, t_node *env)
{
	char	*key;
	int		j;

	j = ft_len_var(lst_key);
	key = ft_substr(lst_key, 0, j);
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (env->value_of_the_key);
		env = env->next;
	}
	return (NULL);
}

void	ft_helper_expand1(t_token **head, t_token **lst, t_node *env)
{
	*head = *lst;
	if ((*head)->prev && (*head)->prev->type == W_SPC)
		(*head) = (*head)->prev;
	if (((*head)->prev && (*head)->prev->type != R_HERDOC) \
		|| (*head)->prev == NULL)
		ft_expand((*lst)->next, env);
}

int	ft_condition_expand(t_token *lst, int q)
{
	if (lst->type == DOLLAR && ft_valid_to_search(lst->next) \
			&& q != 1 && (!lst->prev \
			|| ((lst->prev && ((lst->prev->type != R_HERDOC \
			&& lst->prev->type != W_SPC) || (lst->prev->type == W_SPC \
			&& ((lst->prev->prev \
			&& lst->prev->prev->type != R_HERDOC) || (!lst->prev->prev))))))))
		return (1);
	return (0);
}

void	env_command(t_node **list)
{
	print_list (list);
}
