/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 03:48:42 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/28 08:05:29 by azgaoua          ###   ########.fr       */
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

void ft_args_with_expand(t_tokens **cmdline, t_node *env_nds)
{

	(void)(cmdline);
	(void)(env_nds);
    // int i = 0;
    // int j = 0;
    // // char *name;

    // (void)env_nds;
    // while ((*cmdline)->options[i])
    // {
    //     if ((*cmdline)->options[i][0] == '$' && \
    //             ((*cmdline)->options[i][1] == '_' \
    //             || ft_isalpha((*cmdline)->options[i][1]) == 1))
    //     {
    //         // if (name)
    //         //     free(name);
    //         // name = ft_strdup((*cmdline)->options[i] + 1);
    //         // Check if the variable is in the expand array
    //         if ((*cmdline)->expand[j])
    //         {
    //             printf("<<>>%s\n", (*cmdline)->options[i]);

    //             // Free the original option and replace it with the expanded value
    //             free((*cmdline)->options[i]);
    //             (*cmdline)->options[i] = ft_strdup((*cmdline)->expand[j]);

    //             j++;  // Move to the next variable in (*cmdline)->expand
    //         }
    //     }

    //     i++;

    //     if (!(*cmdline)->options[i])
    //         break;
    // }
}

