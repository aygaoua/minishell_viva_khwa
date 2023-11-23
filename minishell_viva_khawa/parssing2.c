/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:52:53 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/22 23:26:34 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_in_file3(t_tokens **nodes, int i)
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
			return ((*nodes)->i_fd = ERROR, (*nodes)->type = ERROR \
					, printf("minishell: %s: No such file or directory\n", \
					(*nodes)->options[i + 1]), 1);
		else
			(*nodes)->type = IN_FILE;
	}
	else
	{
		(*nodes)->type = ERROR;
		printf("minishell: syntax error near unexpected token `newline'\n");
	}
	return (0);
}

int	ft_get_out_file2(t_tokens **nodes, int i)
{
	(*nodes)->options[i]++;
	if ((*nodes)->options[i] && (*nodes)->options[i][0] == '>')
	{
		(*nodes)->type = -2;
		printf("minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	else if ((*nodes)->options[i])
	{
		if ((*nodes)->type == IN_FILE || (*nodes)->type == IN_HERDOC)
		{
			(*nodes)->o_file = (*nodes)->options[i];
			(*nodes)->o_fd = open((*nodes)->options[i], \
								O_CREAT | O_RDWR, 0644);
		}
	}
	(*nodes)->options[i]--;
	return (0);
}

int	ft_get_out_file3(t_tokens **nodes, int i)
{
	if ((*nodes)->options[i + 1] && (*nodes)->options[i + 1][0] == '>')
	{
		(*nodes)->o_fd = -2;
		printf("minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	else if ((*nodes)->options[i + 1])
	{
		if ((*nodes)->type == IN_FILE || (*nodes)->type == IN_HERDOC)
		{
			printf ("ll kk hh");
			(*nodes)->o_file = (*nodes)->options[i + 1];
			(*nodes)->o_fd = open((*nodes)->options[i + 1], \
								O_CREAT | O_RDWR, 0644);
		}
	}
	else
	{
		(*nodes)->type = ERROR;
		printf("minishell: syntax error near unexpected token `newline'\n");
	}
	return (0);
}
