/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:52:53 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/23 06:04:59 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_in_file3(t_tokens **nodes, int i)
{
	if ((*nodes)->options[i + 1] && (*nodes)->options[i + 1][0] == '<')
	{
		(*nodes)->i_fd = -2;
		printf("minishell: syntax error near unexpected token `<'\n");
		// (*nodes)->options[i + 1] = NULL;
		// ft_swap_and_null(&(*nodes)->options, i);
		ft_swap_and_null(&(*nodes)->options, i + 1);
		return (1);
	}
	else if ((*nodes)->options[i + 1])
	{
		(*nodes)->i_file = (*nodes)->options[i + 1];
		(*nodes)->i_fd = open((*nodes)->options[i + 1], O_RDONLY);
		if ((*nodes)->i_fd < 0)
		{
			(*nodes)->i_fd = ERROR;
			(*nodes)->type = ERROR;
			printf("minishell: %s: No such file or directory\n", \
					(*nodes)->options[i + 1]);
			// ft_swap_and_null(&(*nodes)->options, i);
			ft_swap_and_null(&(*nodes)->options, i + 1);
			return (1);
		}
		else
			(*nodes)->type = IN_FILE;
		// (*nodes)->options[i + 1] = NULL;
		// ft_swap_and_null(&(*nodes)->options, i);
		ft_swap_and_null(&(*nodes)->options, i + 1);
	}
	else
	{
		(*nodes)->type = ERROR;
		printf("minishell: syntax error near unexpected token `newline'\n");
	}
	// ft_swap_and_null(&(*nodes)->options, i);
	return (0);
}

int	ft_get_out_file2(t_tokens **nodes, int i)
{
	(*nodes)->options[i]++;
	if ((*nodes)->options[i] && (*nodes)->options[i][0] == '>')
	{
		(*nodes)->o_fd = ERROR;
		(*nodes)->type = ERROR;
		printf("minishell: syntax error near unexpected token `>'\n");
		// (*nodes)->options[i] = NULL;
		ft_swap_and_null(&(*nodes)->options, i);
		return (1);
	}
	else if ((*nodes)->options[i])
	{
		if ((*nodes)->o_fd > 0)
			close((*nodes)->o_fd);
		(*nodes)->o_file = (*nodes)->options[i];
		(*nodes)->o_fd = open((*nodes)->options[i], \
							O_CREAT | O_WRONLY | O_TRUNC, 0644);
		(*nodes)->type = OUT_FILE;
		// (*nodes)->options[i] = NULL;
		ft_swap_and_null(&(*nodes)->options, i);
	}
	(*nodes)->options[i]--;
	return (0);
}

int	ft_get_out_file3(t_tokens **nodes, int i)
{
	if ((*nodes)->options[i + 1] && (*nodes)->options[i + 1][0] == '>')
	{
		(*nodes)->type = ERROR;
		(*nodes)->o_fd = ERROR;
		printf("minishell: syntax error near unexpected token `>'\n");
		// (*nodes)->options[i + 1] = NULL;
		ft_swap_and_null(&(*nodes)->options, i + 1);
		return (1);
	}
	else if ((*nodes)->options[i + 1])
	{
		if ((*nodes)->o_fd > 0)
			close((*nodes)->o_fd);
		(*nodes)->o_file = (*nodes)->options[i + 1];
		(*nodes)->o_fd = open((*nodes)->options[i + 1], \
							O_CREAT | O_WRONLY | O_TRUNC, 0644);
		(*nodes)->type = OUT_FILE;
		// (*nodes)->options[i + 1] = NULL;
		ft_swap_and_null(&(*nodes)->options, i + 1);
	}
	else
	{
		(*nodes)->type = ERROR;
		(*nodes)->o_fd = ERROR;
		printf("minishell: syntax error near unexpected token `newline'\n");
	}
	return (0);
}
