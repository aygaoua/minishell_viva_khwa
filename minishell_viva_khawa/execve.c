/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 02:14:28 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/30 15:00:34 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_plus(char *str)
{
	int		indx;
	char	*key;

	indx = 0;
	key = ft_calloc (ft_strlen (str) + 2, sizeof (char));
	while (str[indx])
	{
		if (str[indx + 1] == '\0')
		{
			key[indx] = str[indx];
			key[indx + 1] = '=';
			key[indx + 2] = '\0';
			return (key);
		}
		key[indx] = str[indx];
		indx++;
	}
	return (NULL);
}

char	**make_list_arr(t_node **list)
{
	t_node	*add;
	char	**arr;
	char	*ptr;
	int		row;

	if (!list || !(*list))
		return (NULL);
	add = (*list);
	arr = (char **) ft_calloc (ft_lstsize_k ((*list)) + 1, sizeof (char *));
	if (!arr)
		return (NULL);
	row = 0;
	while (add)
	{
		ptr = add_plus(add->key);
		arr[row] = ft_strjoin (ptr, add->value_of_the_key);
		free (ptr);
		add = add->next;
		row++;
	}
	return (arr);
}

void	ft_free_matrix_contnt(char **arr)
{
	int	row;

	row = 0;
	while (arr[row])
	{
		free (arr[row]);
		row++;
	}
	free (arr);
}

void	print_2d(char **arr)
{
	int	indx;

	indx = 0;
	while (arr[indx])
	{
		printf ("> %s\n", arr[indx]);
		indx++;
	}
}
