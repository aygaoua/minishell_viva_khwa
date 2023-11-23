/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 03:48:42 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/23 20:54:56 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_swap_and_null(char ***array, int row) {
    if (*array == NULL || row < 0 || (*array)[row] == NULL) {
        // (*array)[row] = NULL;
        // Handle invalid input or if the specified element is already NULL
        return;
    }
    printf("***********|||||||||||||*********\n%s - %d\n***********|||||||||||||*********\n", (*array)[row], row);

    char *temp; // Temporary variable for swapping

    // Set the specified element to NULL

    // Continue swapping until the next element after the specified row is NULL
    while ((*array)[row + 1] != NULL) {
        // Swap the current element with the next element
        temp = (*array)[row];
        (*array)[row] = (*array)[row + 1];
        (*array)[row + 1] = temp;

        // Move to the next row
        row++;
    }
    (*array)[row] = NULL;
    // (*array)[row] = NULL;
}


// void ft_swap_and_null(char ***array, int row) {
//     if (*array == NULL || row < 0) {
//         return;
//     }
//     char *temp; // Temporary variable for swapping

//     // Continue swapping until the next element after the specified row is NULL
//     while ((*array)[row + 1] != NULL) {
//         // Swap the current element with the next element
//         temp = (*array)[row];
//         (*array)[row] = (*array)[row + 1];
//         (*array)[row + 1] = temp;

//         // Move to the next row
//         row++;
//     }

//     // Set the last element to NULL
//     (*array)[row - 1] = NULL;
// }


// void ft_swap_and_null(char ***array, int row)
// {
//     char *s;

//     while ((*array)[row + 1])
//     {
//         s = (*array)[row];
//         (*array)[row] = (*array)[row + 1];
//         (*array)[row + 1] = s;
//         row++;
//     }
//     (*array)[row] = NULL;
// }