/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 03:48:42 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/23 05:15:18 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_swap_and_null(char ***array, int row)
{
    char *s;

    while ((*array)[row])
    {
        if ((*array)[row + 1])
        {
            s = (*array)[row];
            (*array)[row] = (*array)[row + 1];
            (*array)[row + 1] = s;
        }
        row++;
    }
    (*array)[row - 1] = NULL;
}