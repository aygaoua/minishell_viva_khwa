/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:18:30 by azgaoua           #+#    #+#             */
/*   Updated: 2023/10/31 19:27:50 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_debug(t_tokens *nodes)
{
    int j;
    int i;
    i = 0;
    j = 0;
    while (nodes)
    {
        printf("cmd[%d] = ---%s---\n", j, nodes->cmd);
        printf("in_file %d = ---%s---\n", j, nodes->i_file);
        printf("in_fd %d = ---\'%d\'---\n", j, nodes->i_fd);
        j++;
        i = 0;
        while (nodes->options[i])
        {
            printf("option[%d] = ---\"%s\"---\n", i, nodes->options[i]);
            i++;
        }
        nodes = nodes->next;
    }
}

void    ft_get_real_args(t_tokens **cmdline)
{
    t_tokens    *nodes = NULL;
    char        **splt;
    int         i;
    int         j;

    i = 0;
    j = 0;
    nodes = *cmdline;
    splt = ft_split(nodes->input, '|');
    while (splt[i])
    {
        ft_lstadd_back(&nodes, ft_lstnew(splt[i]));
        i++;
    }
    nodes = *cmdline;
    while (nodes)
    {
        nodes->options = ft_split(nodes->cmd, ' ');
        nodes = nodes->next;
    }
    nodes = *cmdline;
    ft_get_in_file(cmdline);
    nodes = *cmdline;
    ft_debug(nodes);
}

void    ft_get_in_file(t_tokens **cmdline)
{
    t_tokens    *nodes = NULL;
    int         i;

    nodes = *cmdline;
    while (nodes)
    {
        i = 0;
        while (nodes->options[i])
        {
            if (nodes->options[i][0] == '<' && nodes->options[i][1] == '<')
            {
                if (nodes->options[i + 1])
                {
                    nodes->dlmtr = nodes->options[i + 1];
                    nodes->type = in_heredoc;
                }
                else
                    nodes->type = error;
            }
            else if (nodes->options[i][0] == '<')
            {
                if (nodes->options[i + 1])
                {
                    nodes->i_file = nodes->options[i + 1];
                    nodes->i_fd = open(nodes->options[i + 1], O_RDONLY);
                    if (nodes->i_fd <= 0)
                    {
                        nodes->i_fd = -2;
                        printf("%s: No such file or directory", nodes->options[i + 1]);
                        break;
                    }
                    else
                        nodes->type = in_file;
                }
                else
                    nodes->type = error;
            }
            i++;
        }
        nodes = nodes->next;
    }
    nodes = *cmdline;
}
