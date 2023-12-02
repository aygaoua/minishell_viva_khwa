/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:55:19 by momihamm          #+#    #+#             */
/*   Updated: 2023/12/02 00:14:03 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (arg_path (arg[0]) == 0)
	{
		if (chdir (arg[0]) == 0)
		{
			update_env (env);
			return ;
		}
		else
		{
			printf ("minishell-1$: cd: %s: No such file or directory\n", arg[0]);
			ft_exit_status(1);
		}
	}
}
