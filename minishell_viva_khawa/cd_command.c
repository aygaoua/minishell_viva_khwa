/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:55:19 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/01 09:55:10 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_node	*get_node(t_node **list, char *str)
// {
// 	t_node	*ptr;

// 	ptr = (*list);
// 	while (ptr)
// 	{
// 		if (ft_strcmp (ptr->key, str) == 0)
// 			return (ptr);
// 		ptr = ptr->next;
// 	}
// 	return (NULL);
// }

// int	arg_path(char *str)
// {
// 	if (str[0] != '-' && str[0] != '~')
// 		return (0);
// 	else if (str[0] == '-')
// 		return (1);
// 	return (-1);
// }

// void	print_oldpwd(t_node **my_env)
// {
// 	t_node	*ptr;

// 	if (!my_env || !(*my_env))
// 		return ;
// 	ptr = (*my_env);
// 	while (ptr)
// 	{
// 		if (ptr && ft_strcmp (ptr->key, "OLDPWD") == 0)
// 		{
// 			printf ("%s\n", ptr->value_of_the_key);
// 			return ;
// 		}
// 		ptr = ptr->next;
// 	}
// }

void	update_env(t_node **my_env)
{
	t_node	*old;
	t_node	*new;
	char	*ptr;
	char	*pwd;

	old = get_node (my_env, "OLDPWD");
	new = get_node (my_env, "PWD");
	ptr = old->value_of_the_key;
	old->value_of_the_key = new->value_of_the_key;
	// free (ptr);
	pwd = getcwd (NULL, 0);
	ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(pwd));
	new->value_of_the_key = pwd;
}

char	*go_home(t_node **my_env)
{
	t_node	*home;

	home = get_node (my_env, "HOME");
	if (!home)
	{
		printf (" cd: HOME not set\n");
		ft_exit_status(1);
		return (NULL);
	}
	else
		return (home->value_of_the_key);
	return (NULL);
}

int	home(t_node **my_env, char *str)
{
	char	*path;

	if (!str)
	{
		path = go_home (my_env);
		if (chdir (path) == 0)
			return (0);
		else
			return (1);
	}
	return (1);
}

void	cd_command(t_node **env, char **arg)
{
	if (!arg || !arg[0])
	{
		if ((home (env, arg[0]) == 0))
			return ;
	}
	if (arg_path (arg[0]) == 0)
	{
		if (chdir (arg[0]) == 0)
		{
			update_env (env);
			return ;
		}
		else
		{
			printf (" cd: %s: No such file or directory\n", arg[0]);
			ft_exit_status(1);
		}

	}
}
