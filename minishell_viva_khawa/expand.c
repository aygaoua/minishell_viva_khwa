/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:14:35 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/16 16:24:47 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_expand_check(t_tokens **cmdline)
{
    int i;
    int k;
    // int j;
    char *s;

    i = 0;
    k = 0;
    s = NULL;
    if (ft_elem_count((*cmdline)->cmd, '$'))
    {
        // while ((*cmdline)->cmd[i])
        // {
            while ((*cmdline)->cmd[i] != '$')
                i++;
            i++;
            k = i;
            while ((*cmdline)->cmd[k] != ' ' && (*cmdline)->cmd[k])
                k++;
            s = malloc(k + 1);
            k = 0;
            while ((*cmdline)->cmd[i] != ' ' && (*cmdline)->cmd[i])
            {
                s[k] = (*cmdline)->cmd[i];
                k++;
                i++;
            }
            s[k] = '\0';
        // }
    }
    printf("$->%s\n", s);
    return (s);
}
