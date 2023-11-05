/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:08:11 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/05 16:37:18 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    t_tokens    *cmdline = NULL;
    char        *str;

    str = NULL;
    cmdline = malloc (sizeof(t_tokens));
    if (!cmdline)
        return (0);
    while (0 == 0)
    {
        cmdline->input = readline("minishell-1$ ");
        add_history(cmdline->input);
        cmdline = ft_lstnew(cmdline->input);
        ft_get_real_args(&cmdline);
    }
    return(0);
}