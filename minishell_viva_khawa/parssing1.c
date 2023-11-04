/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:29:52 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/04 16:33:21 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_infile_while(t_tokens **nodes, int i)
{
    while ((*nodes)->options && (*nodes)->options[i])
    {
        if ((*nodes)->options[i][0] == '<' && (*nodes)->options[i][1] == '<')
        {
            if (ft_get_in_file1(nodes, i))
                return (1);
        }
        else if ((*nodes)->options[i][0] == '<' && (*nodes)->options[i][1] != '<')
        {
            if (ft_get_in_file2(nodes, i))
                return (1);
        }
        else if ((*nodes)->options[i][0] && (*nodes)->options[i][0] == '<')
        {
            if (ft_get_in_file3(nodes, i))
                return (1);
        }
        i++;
    }
    return (0);
}