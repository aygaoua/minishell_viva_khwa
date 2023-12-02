/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:04:39 by azgaoua           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/01 23:42:16 by azgaoua          ###   ########.fr       */
=======
/*   Updated: 2023/11/29 02:30:51 by azgaoua          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	key_len = ft_len_var(full_key);
	full_key_len = ft_strlen(full_key);
	rest_key = ft_substr(full_key, key_len, full_key_len - key_len);
	if (full_key[0] == '?')
	{
		lst->value = ft_itoa(ft_exit_status(-1));
		return ;
	}
	if (full_key[0] != '_' || ft_isalpha(full_key[0]) == 0)
	{
		lst->value = ft_strjoin(full_key + 1, rest_key);
		return ;
	}
	result = ft_strjoin(NULL, rest_key);
	lst->value = ft_strjoin(NULL, rest_key);
	return ;
}

void	ft_helper_expand2(t_token **lst, char **inside, \
							t_token **new_lst, int q)
{
	if ((*lst)->type == WORD && ((*lst)->prev \
	&& (*lst)->prev->type == DOLLAR \
	&& (((*lst)->prev->prev \
	&& (((*lst)->prev->prev->type == W_SPC \
	&& (*lst)->prev->prev->prev \
	&& (*lst)->prev->prev->prev->type == R_HERDOC) \
	|| (*lst)->prev->prev->type == R_HERDOC)))))
		*inside = ft_strjoin(ft_strdup("$"), (*lst)->value);
	if (q && (*lst)->value != NULL)
		*inside = ft_strjoin(*inside, (*lst)->value);
	else
		ft_lstadd_back2(new_lst, ft_lstnew2(ft_strdup((*lst)->value), \
			(*lst)->type));
}

int	ft_last_part(t_token **lst, int q)
{
<<<<<<< HEAD
	if ((*lst)->type == DOLLAR && (*lst)->next && ft_valid_to_search
		((*lst)->next) == 0 && q != 1 && (*lst)->next->type != W_SPC)
		return (1);
	return (0);
=======
    char *full_key;
    int key_len;
    int full_key_len;
    char *rest_key;
    char *result;

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
    result = ft_strjoin( NULL, rest_key);
    lst->value = ft_strjoin(NULL, rest_key);
    return ;
>>>>>>> main
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
		else if (ft_condition_expand(lst, q))
			ft_helper_expand1(&head, &lst, env);
		else if (ft_last_part(&lst, q))
			ft_invalid_exp(lst->next);
		else
			ft_helper_expand2(&lst, &inside, &new_lst, q);
		lst = lst->next;
	}
	return (new_lst);
}
