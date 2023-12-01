/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 04:31:31 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 03:06:37 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_token(t_tokens *lst)
{
	t_tokens	*j;
	int			i;

	if (!lst)
		return (0);
	j = lst;
	i = 0;
	while (j != NULL)
	{
		j = lst -> next;
		lst = j;
		i++;
	}
	return (i);
}

// char	*get_path_cmand(char **path, char **command)
// {
// 	char	*slash;
// 	char	*cmd_path;
// 	int		row;

// 	row = 0;
// 	slash = add_slash (command[row]);
// 	cmd_path = NULL;
// 	while (path[row])
// 	{
// 		if (cmd_path)
// 			free (cmd_path);
// 		cmd_path = ft_strjoin (path[row], slash);
// 		if (access (cmd_path, F_OK) == 0)
// 		{
// 			return (cmd_path);
// 		}
// 		row++;
// 	}
// 	free (cmd_path);
// 	ft_free_matrix_contnt (path);
// 	free (slash);
// 	return (NULL);
// }
