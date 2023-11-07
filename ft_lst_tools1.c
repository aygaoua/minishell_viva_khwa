/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_tools1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:06:29 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/05 21:52:59 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_tokens **lst)
{
	t_tokens	*helper;
	int			i;

	i = 0;
	if (!lst || !*lst)
		return ;
	else
	{
		while (*lst)
		{
			helper = (*lst)-> next;
            if ((*lst)->cmd)
			    free((*lst)->cmd);
			while ((*lst)->options[i])
            {
				free((*lst)->options[i]);
                i++;
            }
            if ((*lst)->options)
			    free((*lst)->options);
            if ((*lst)->input)
    			free((*lst)->input);
			if ((*lst)->i_file)
                free((*lst)->i_file);
            if ((*lst)->o_file)
			    free((*lst)->o_file);
            if ((*lst)->dlmtr)
			    free((*lst)->dlmtr);
			if (*lst)
                free(*lst);
			*lst = helper;
		}
		*lst = NULL;
        printf("----------->\n");
	}
}
