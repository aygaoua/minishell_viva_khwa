/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:49:44 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/16 14:45:37 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_elem_count(char *s, char c)
{
    int i;
    int rtn;

    i = 0;
    rtn = 0;
    if (!s)
        return (0);
    while (s[i])
    {
        if (s[i] == c)
            rtn++;
        i++;
    }
    return (rtn);
}

int    ft_quots(t_tokens **cmdline)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    if (ft_elem_count((*cmdline)->cmd, '"') || ft_elem_count((*cmdline)->cmd, '\''))
    {
        if (ft_elem_count((*cmdline)->cmd, '"') % 2 == 1 \
            || ft_elem_count((*cmdline)->cmd, '\'') % 2 == 1)
            return (1);
        else
        {
            if (ft_elem_count((*cmdline)->cmd, '\''))
            {
                while ((*cmdline)->cmd[i])
                {
                    if ((*cmdline)->cmd[i] == '\'')
                        i++;
                    (*cmdline)->input[j] = (*cmdline)->cmd[i];
                    j++;
                    i++;
                }
                (*cmdline)->cmd[j] = '\0';
            }
        }
    }
    return (0);
}

char    *ft_s_quots(char *cmd, int *i)
{
    int     k;
    char    *s;

    k = 0;
    s = malloc(ft_strlen(cmd) + 1);
    if (!s)
        return (NULL);
    // allocation done!!
    if (ft_elem_count(cmd, '\'') \
        && ft_elem_count(cmd, '\'') % 2 == 0)
    {
        while (cmd[*i])
        {
            if (cmd[*i] == '\'')
            {
                (*i)++;
                while (cmd[*i] != '\'')
                {
                    s[k] = cmd[*i];
                    k++;
                    (*i)++;
                }
            }
            (*i)++;
        }
    }
    s[k] = '\0';
    printf("qouts == \"%s\"\n", s);
    return (s);
}
