/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:04:39 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 02:37:18 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_expand(t_token *lst, t_node *env)
{
	char	*full_key;
	char	*env_val;
	int		key_len;
	int		full_key_len;
	char	*rest_key;

	full_key = lst->value;
	env_val = ft_get_env(full_key, env);
	key_len = ft_len_var(full_key);
	full_key_len = ft_strlen(full_key);
	rest_key = ft_substr(full_key, key_len, full_key_len - key_len);
	if (env_val)
		lst->value = ft_strjoin(env_val, rest_key);
	else
		lst->value = ft_strjoin(NULL, rest_key);
	return ;
}

void	ft_invalid_exp(t_token *lst)
{
	char	*full_key;
	int		key_len;
	int		full_key_len;
	char	*rest_key;
	char	*result;

	if (lst == NULL)
		return ;
	full_key = lst->value;
	if (full_key[0] != '_' || ft_isalpha(full_key[0] == 0))
	{
		lst->value = ft_strjoin(full_key + 1, rest_key);
		return ;
	}
	key_len = ft_len_var(full_key);
	full_key_len = ft_strlen(full_key);
	rest_key = ft_substr(full_key, key_len, full_key_len - key_len);
	result = ft_strjoin(NULL, rest_key);
	lst->value = ft_strjoin(NULL, rest_key);
	return ;
}

t_token	*ft_expand_and_quots(t_token *lst, t_node *env)
{
	t_token	*new_lst;
	t_token	*head;
	char	*inside;
	int		q;

	new_lst = NULL;
	inside = NULL;
	q = 0;
	head = lst;
	while (lst)
	{
		if (lst->type == S_QUOT && q != 2)
			ft_quote_hand(&q, 1, &inside, &new_lst);
		else if (lst->type == D_QUOT && q != 1)
			ft_quote_hand(&q, 2, &inside, &new_lst);
		else if (lst->type == DOLLAR && ft_valid_to_search(lst->next) \
				&& q != 1 && (!lst->prev || ((lst->prev && lst->prev->type != R_HERDOC) || (lst->prev->type == W_SPC && lst->prev->prev && lst->prev->prev->type != R_HERDOC))))
		{
			head = lst;
			if (head->prev && head->prev->type == W_SPC)
				head = head->prev;
			if ((head->prev && head->prev->type != R_HERDOC) || lst->prev == NULL)
			{
				ft_expand(lst->next, env);
			}
		}
		else if (lst->type == DOLLAR && ft_valid_to_search(lst->next) == 0 \
					&& q != 1 && lst->next && lst->next->type != W_SPC)
		{
			ft_invalid_exp(lst->next);
		}
		else if (q && lst->value != NULL)
			inside = ft_strjoin(inside, lst->value);
		else 
			ft_lstadd_back2(&new_lst, ft_lstnew2(ft_strdup(lst->value), \
							lst->type));
		lst = lst->next;
	}
	return (new_lst);
}
