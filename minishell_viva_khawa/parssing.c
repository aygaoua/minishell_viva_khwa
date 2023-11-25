/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:18:30 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/25 05:15:22 by azgaoua          ###   ########.fr       */
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
		printf ("out_file %d = ---%s---\n", j, nodes->o_file);
		printf ("out_fd %d = ---\'%d\'---\n", j, nodes->o_fd);
		printf ("delimiter %d = ---\'%s\'---\n", j, nodes->dlmtr);
		j++;
		i = 0;
		while (nodes->options && nodes->options[i])
		{
			printf ("option[%d] = ---\"%s\"---\n", i, nodes->options[i]);
			i++;
		}
		printf ("type_i %d = --->%d<---\n", j, nodes->type_i);
		printf ("type_j %d = --->%d<---\n", j, nodes->type_o);
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
		if (ft_quots(&nodes) == 1)
		{
			printf("minishell: syntax error near unexpected token \'\n");
			return ;
		}
		else
		{
			nodes = *cmdline;
			while (nodes)
			{
				nodes->options = ft_split_p(nodes->cmd, ' ');
				nodes = nodes->next;
			}
			nodes = *cmdline;
			ft_expand_check(cmdline);
			nodes = *cmdline;
			ft_get_in_files(&nodes);
			nodes = *cmdline;
			ft_get_out_files(&nodes);
		}
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

int	ft_get_in_file1(t_tokens **nodes, int i)
{
	if ((*nodes)->options[i + 1] != NULL && (*nodes)->options[i + 1][0] != '<')
	{
		(*nodes)->dlmtr = (*nodes)->options[i + 1];
		(*nodes)->type_i = IN_HERDOC;
		ft_swap_and_null(&(*nodes)->options, i);
	}
	else
	{
		(*nodes)->type_i = ERROR;
		printf("minishell: syntax error near unexpected token `newline'\n");
		while ((*nodes)->options[0])
				ft_swap_and_null(&(*nodes)->options, 0);
		return (1);
	}
	ft_swap_and_null(&(*nodes)->options, i);
	return (0);
}

int	ft_get_in_file2(t_tokens **nodes, int i)
{
	(*nodes)->options[i]++;
	if ((*nodes)->options[i] && (*nodes)->options[i][0] == '<')
	{
		(*nodes)->type_i = -2;
		printf("minishell: syntax error near unexpected token `<'\n");
		--(*nodes)->options[i];
		while ((*nodes)->options[0])
				ft_swap_and_null(&(*nodes)->options, 0);
		return (1);
	}
	else if ((*nodes)->options[i])
	{
		(*nodes)->i_file = (*nodes)->options[i];
		(*nodes)->i_fd = open((*nodes)->options[i], O_RDONLY);
		if ((*nodes)->i_fd < 0)
		{
			(*nodes)->type_i = ERROR;
			(*nodes)->i_fd = ERROR;
			perror("open");
			// printf("minishell: %s: No such file or directory\n", \
			// (*nodes)->options[i]);
			--(*nodes)->options[i];
			while ((*nodes)->options[0])
				ft_swap_and_null(&(*nodes)->options, 0);
			return (1);
		}
		else
			(*nodes)->type_i = IN_FILE;
	}
	--(*nodes)->options[i];
	ft_swap_and_null(&(*nodes)->options, i);
	return (0);
}
