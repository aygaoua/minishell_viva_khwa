/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:55:19 by momihamm          #+#    #+#             */
/*   Updated: 2023/11/20 00:10:37 by azgaoua          ###   ########.fr       */
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

	printf ("AAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	old = get_node (my_env, "OLDPWD");
	new = get_node (my_env, "PWD");
	ptr = old->value_of_the_key;
	old->value_of_the_key = new->value_of_the_key;
	free (ptr);
	// pwd = getcwd (NULL, 0);
	// free (new->value_of_the_key);
	pwd = ft_strdup (getcwd (NULL, 0));
	new->value_of_the_key = pwd;
	// free (ptr);
}

char	*go_home(t_node **my_env)
{
	t_node	*home;

	home = get_node (my_env, "HOME");
	if (!home)
	{
		printf (" cd: HOME not set\n");
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
	printf ("########################################\n############################################\n");
	print_list (env);
	if (!arg || !arg[0])
	{
		// printf ("GO HOME\n");
		if ((home (env, arg[0]) == 0))
			return ;
	}
	// if ((home (env), arg[0]) == 0)
	// 	return ;
	if (arg_path (arg[0]) == 0)
	{
		if (chdir (arg[0]) == 0)
		{
			printf ("+++++|+|+kmi\n");
			// print_export (env); 
			// print_list (env);
			update_env (env);
			printf ("!!!!!!!!!!!!!***************!!!!!!!!!!!!!!!!!**************!!!!!!!!!!!*****************\n");
			// print_export (env);
			print_list (env); 
			return ;
		}
		else
			printf (" cd: %s: No such file or directory\n", arg[0]);
	}
	// else if (arg_path (arg[0]) == 1)
	// {
	// 	printf ("!!!!!!!!!!!!!***************!!!!!!!!!!!!!!!!!**************!!!!!!!!!!!*****************\n");
	// 	if (arg[0][1] == '\0')
	// 	{
	// 		if ((get_node (env), "OLDPWD") == NULL)
	// 		{
	// 			printf (" cd: OLDPWD not set\n");
	// 			return ;
	// 		}
	// 		print_oldpwd(env);
	// 	}
	// }
	// print_list (env);
}
