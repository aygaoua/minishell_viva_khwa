/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:29:52 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/22 23:23:07 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_infile_while(t_tokens **nodes, int *i)
{
	while ((*nodes)->options && (*nodes)->options[*i])
	{
		if ((*nodes)->options[*i][0] == '<' && (*nodes)->options[*i][1] == '<')
		{
			if (ft_get_in_file1(nodes, *i))
				return (1);
		}
		else if ((*nodes)->options[*i][0] == '<' && (*nodes)->options[*i][1] && \
					(*nodes)->options[*i][1] != '<')
		{
			if (ft_get_in_file2(nodes, *i))
				return (1);
		}
		else if ((*nodes)->options[*i][0] && (*nodes)->options[*i][0] == '<')
		{
			if (ft_get_in_file3(nodes, *i))
				return (1);
		}
		(*i)++;
	}
	return (0);
}

int	ft_get_cmd_pipe_elems(t_tokens **nodes)
{
	char	**splt;
	int		i;

	i = 0;
	while ((*nodes)->input[i] == ' ' || (*nodes)->input[i] == '\t')
		i++;
	if ((*nodes)->input[i] == '|')
		return (printf("minishell: syntax error near unexpected token `|'\n"), \
				1);
	i = 0;
	splt = ft_split((*nodes)->input, '|');
	if (ft_strchr((*nodes)->input, '|'))
	{
		while (splt[i])
		{
			ft_lstadd_back(nodes, ft_lstnew(splt[i]));
			i++;
		}
	}
	i = -1;
	return (0);
}

void	ft_get_out_files(t_tokens **cmdline)
{
	t_tokens	*nodes;
	int			i;

	nodes = *cmdline;
	while (nodes)
	{
		i = 0;
		if (ft_outfile_while(&nodes, &i))
			break ;
		nodes = nodes->next;
	}
	nodes = *cmdline;
}

int	ft_outfile_while(t_tokens **nodes, int *i)
{
	while ((*nodes)->options && (*nodes)->options[*i])
	{
		if ((*nodes)->options[*i][0] == '>' && (*nodes)->options[*i][1] == '>')
		{
			if (ft_get_out_file1(nodes, *i))
				return (1);
		}
		else if ((*nodes)->options[*i][0] == '>' && (*nodes)->options[*i][1] && \
					(*nodes)->options[*i][1] != '>')
		{
			if (ft_get_out_file2(nodes, *i))
				return (1);
		}
		else if ((*nodes)->options[*i][0] && (*nodes)->options[*i][0] == '>')
		{
			if (ft_get_out_file3(nodes, *i))
				return (1);
		}
		(*i)++;
	}
	return (0);
}

int	ft_get_out_file1(t_tokens **nodes, int i)
{
	if ((*nodes)->options[i + 1] != NULL)
	{
		if ((*nodes)->type == IN_FILE || (*nodes)->type == IN_HERDOC)
		{
			(*nodes)->o_file = (*nodes)->options[i + 1];
			(*nodes)->o_fd = open((*nodes)->options[i + 1], \
									O_CREAT | O_RDWR, 0644);
		}
	}
	else
	{
		(*nodes)->type = ERROR;
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
