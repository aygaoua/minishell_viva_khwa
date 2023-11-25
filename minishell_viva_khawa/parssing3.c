/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 03:48:42 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/25 08:48:01 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_swap_and_null(char ***array, int row)
{
    char *temp;

    if (*array == NULL || row < 0 || (*array)[row] == NULL)
        return;
    while ((*array)[row + 1] != NULL)
    {
        temp = (*array)[row];
        (*array)[row] = (*array)[row + 1];
        (*array)[row + 1] = temp;
        row++;
    }
    (*array)[row] = NULL;
}

void    ft_print_error(char *s)
{
    write(2, &s, ft_strlen(s));
}
