/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:04:39 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/29 01:12:03 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_valid_to_search(t_token *lst)
{
    int i;

    i = 0;
    if (lst && (lst->type == WORD \
        && (lst->value[0] == '_' || ft_isalpha(lst->value[0]))))
        return (1);
    return (0);
}

void ft_quote_hand(int *q, int type, char **inside, t_token **lst)
{
    if(*q == 0)
        *q = type;
    else if (*q == type)
    {
        *q = 0;
        ft_lstadd_back2(lst, ft_lstnew2(*inside, WORD));
        *inside = NULL;
    }
}

char *ft_strjoin_f(char *s1, char *s2, int a, int b)
{
    char *str = ft_strjoin(s1, s2);
    if(a)
        free(s1);
    if(b)
        free(s2);
    return str;
}

int ft_len_var(char *s)
{
    int j;

    j = 0;
    while (s[j] && (s[j] == '_' || ft_isalpha(s[j]) \
            || ft_isdigit(s[j])))
        j++;
    return (j);
}

char *ft_get_env(char* lst_key, t_node *env)
{
    char *key;
    int j;

    j = ft_len_var(lst_key);
    key = ft_substr(lst_key, 0, j);
    while (env)
    {
        if (ft_strcmp(key, env->key) == 0)
            return (free(key), env->value_of_the_key);
        env = env->next;
    }
    return (free(key), NULL);
}

void ft_expand(t_token *lst, t_node *env)
{
    char *full_key;
    char *env_val;
    int key_len;
    int full_key_len;
    char *rest_key;
    char *result;

    full_key = lst->value;
    env_val = ft_get_env(full_key, env);
    key_len = ft_len_var(full_key);
    full_key_len = ft_strlen(full_key);
    rest_key = ft_substr(full_key, key_len, full_key_len - key_len);
    result = ft_strjoin(env_val, rest_key);
    if (env_val)
        lst->value = result;
    else
        lst->value = ft_strjoin(NULL, rest_key);
    return ;
}

void ft_invalid_exp(t_token *lst)
{
    char *full_key;
    int key_len;
    int full_key_len;
    char *rest_key;
    char *result;

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
}

t_token *ft_expand_and_quots(t_token *lst, t_node *env)
{
    t_token *new_lst;
    char    *inside;
    int     q;

    new_lst = NULL;
    inside = NULL;  
    q = 0;
    while(lst)
    {
        if(lst->type == S_QUOT && q != 2)
            ft_quote_hand(&q , 1, &inside, &new_lst);
        else if(lst->type == D_QUOT && q != 1)
            ft_quote_hand(&q , 2, &inside, &new_lst);
        else if(lst->type == DOLLAR && ft_valid_to_search(lst->next) && q != 1)
            ft_expand(lst->next, env);
        else if (lst->type == DOLLAR && ft_valid_to_search(lst->next) == 0 && q != 1)
            ft_invalid_exp(lst->next);
        else if(q && lst->value != NULL)
            inside = ft_strjoin_f(inside, lst->value, 1, 0);
        else 
            ft_lstadd_back2(&new_lst, ft_lstnew2(lst->value, lst->type));
        lst = lst->next;
    }
    return (new_lst);
}
