/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:18:30 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/07 15:52:35 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_debug(t_tokens *nodes)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (nodes)
	{
		printf ("cmd[%d] = ---%s---\n", j, nodes->cmd);
		printf ("in_file %d = ---%s---\n", j, nodes->i_file);
		printf ("in_fd %d = ---\'%d\'---\n", j, nodes->i_fd);
		printf ("in_file %d = ---%s---\n", j, nodes->o_file);
		printf ("in_fd %d = ---\'%d\'---\n", j, nodes->o_fd);
		printf ("delimiter %d = ---\'%s\'---\n", j, nodes->dlmtr);
		j++;
		i = 0;
		while (nodes->options && nodes->options[i])
		{
			printf ("option[%d] = ---\"%s\"---\n", i, nodes->options[i]);
			i++;
		}
		printf ("type %d = --->%d<---\n", j, nodes->type);
		nodes = nodes->next;
	}
}

void	ft_get_real_args(t_tokens **cmdline)
{
	t_tokens	*nodes;
	int			j;

	j = 0;
	nodes = NULL;
	nodes = *cmdline;
	if (ft_get_cmd_pipe_elems(&nodes) == 0)
	{
		nodes = *cmdline;
		while (nodes)
		{
			nodes->options = ft_split(nodes->cmd, ' ');
			nodes = nodes->next;
		}
		nodes = *cmdline;
		ft_get_in_files(cmdline);
		nodes = *cmdline;
		ft_get_out_files(cmdline);
		// ft_lstclear(cmdline);
		nodes = *cmdline;
		ft_debug(nodes);
	}
}

void	ft_get_in_files(t_tokens **cmdline)
{
	t_tokens	*nodes;
	int			i;

	nodes = *cmdline;
	while (nodes)
	{
		i = 0;
		if (ft_infile_while(&nodes, &i))
			break ;
		nodes = nodes->next;
	}
	nodes = *cmdline;
}

int    ft_get_in_file1(t_tokens **nodes, int i)
{
	if ((*nodes)->options[i + 1] != NULL && (*nodes)->options[i + 1][0] != '<')
	{
		(*nodes)->dlmtr = (*nodes)->options[i + 1];
		(*nodes)->type = in_heredoc;
	}
	else
	{
		(*nodes)->type = error;
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int    ft_get_in_file2(t_tokens **nodes, int i)
{
	(*nodes)->options[i]++;
	if ((*nodes)->options[i] && (*nodes)->options[i][0] == '<')
	{
		(*nodes)->type = -2;
		printf("minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	else if ((*nodes)->options[i])
	{
		(*nodes)->i_file = (*nodes)->options[i];
		(*nodes)->i_fd = open((*nodes)->options[i], O_RDONLY);
		if ((*nodes)->i_fd < 0)
		{
			(*nodes)->type = -2;
			(*nodes)->i_fd = -2;
			printf("minishell: %s: No such file or directory\n", (*nodes)->options[i]);
			return (1);
		}
		else
			(*nodes)->type = in_file;
	}
	(*nodes)->options[i]--;
	return(0);
}

int    ft_get_in_file3(t_tokens **nodes, int i)
{
	if ((*nodes)->options[i + 1] && (*nodes)->options[i + 1][0] == '<')
	{
		(*nodes)->i_fd = -2;
		printf("minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	else if ((*nodes)->options[i + 1])
	{
		(*nodes)->i_file = (*nodes)->options[i + 1];
		(*nodes)->i_fd = open((*nodes)->options[i + 1], O_RDONLY);
		if ((*nodes)->i_fd < 0)
		{
			(*nodes)->i_fd = -2;
			printf("minishell: %s: No such file or directory\n", (*nodes)->options[i + 1]);
			return (1);
		}
		else
			(*nodes)->type = in_file;
	}
	else
	{
		(*nodes)->type = error;
		printf("minishell: syntax error near unexpected token `newline'\n");
	}
	return (0);
}
