/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:46:13 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/30 13:33:19 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_len(char *str, char c)
// {
// 	int	len;

// 	len = 0;
// 	while (str[len] && str[len] != c)
// 		len++;
// 	return (len);
// }

// int	is_ther_the_win_char(char *str, char c, int len)
// {
// 	int	indx;

// 	indx = 0;
// 	while (indx < len && str[indx])
// 	{
// 		if (str[indx] == c)
// 			return (1);
// 		indx++;
// 	}
// 	return (0);
// }

// char	*ft_frontcpy(char *dst, char *src, char del)
// {
// 	int	indx;

// 	if (!src)
// 		return (NULL);
// 	indx = 0;
// 	if (!dst)
// 		dst = ft_calloc (ft_len (src, del) + 1, sizeof (char));
// 	if (!dst)
// 		return (NULL);
// 	while (src[indx] && src[indx] != del)
// 	{
// 		dst[indx] = src[indx];
// 		indx++;
// 	}
// 	dst[indx] = '\0';
// 	return (dst);
// }

// char	*ft_backcpy(char *dst, char *src, char del)
// {
// 	int	indx;
// 	int	indj;
// 	int	len;

// 	if (!src)
// 		return (NULL);
// 	if (is_ther_the_win_char(src, del, ft_strlen (src)) == 0)
// 		return (NULL);
// 	indx = 0;
// 	indj = 0;
// 	len = ft_strlen (src) - ft_len (src, del);
// 	if (!dst)
// 		dst = ft_calloc (len + 1, sizeof (char));
// 	while (src[indx] && src[indx] != del)
// 		indx++;
// 	if (src[indx] == del)
// 	{
// 		indx++;
// 		while (src[indx])
// 			dst[indj++] = src[indx++];
// 		dst[indj] = '\0';
// 	}
// 	return (dst);
// }

t_node	**take_env(char **env)
{
	t_node	**list;
	int		row;

	list = malloc (sizeof (t_node *));
	if (!list)
		return (NULL);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(list));
	(*list) = NULL;
	row = 0;
	while (env[row] != NULL)
	{
		ft_lstadd_back_k (list, ft_lstnew_k (env[row]));
		row++;
	}
	return (list);
}

void	print_list(t_node **list)
{
	t_node	*ptr;

	ptr = (*list);
	while (ptr)
	{
		printf ("%s=%s\n", ptr->key, ptr->value_of_the_key);
		ptr = ptr->next;
	}
}

void	ft_free_contnue(t_node **lst)
{
	t_node	*ptr;

	if (!lst)
		return ;
	if (!(*lst))
		return ;
	ptr = (*lst);
	while (ptr)
	{
		free (ptr->key);
		free (ptr->value_of_the_key);
		ptr = ptr->next;
	}
}

void	ft_free_list(t_node **list)
{
	t_node	*ptr0;
	t_node	*ptr1;

	if (!list)
		return ;
	if (!(*list))
		return ;
	ptr0 = (*list);
	while (ptr0)
	{
		ptr1 = ptr0->next;
		free (ptr0);
		ptr0 = ptr1;
	}
	free (list);
}

void	env_command(char **env)
{
	t_node	**list;

	if (!env || !env[0])
		return ;
	list = take_env (env);
	print_list (list);
	ft_free_contnue (list);
	ft_free_list (list);
}
