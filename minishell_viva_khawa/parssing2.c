/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:52:53 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/24 05:23:10 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	ft_free_tab_2(char ***arr)
{
	int	row;

	row = 0;
	while ((*arr)[row])
	{
		free ((*arr)[row]);
		row++;
	}
}

int	ft_get_in_file3(t_tokens **nodes, int i)
{
	if ((*nodes)->options[i + 1] && (*nodes)->options[i + 1][0] == '<')
	{
		(*nodes)->i_fd = -2;
		printf("minishell: syntax error near unexpected token `<'\n");
		ft_swap_and_null(&(*nodes)->options, i);
		ft_swap_and_null(&(*nodes)->options, i);
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
			printf("minishell: %s:%s\n", \
					(*nodes)->options[i + 1], strerror(errno));
			// perror("");
			// ft_free_tab_2(&(*nodes)->options);
			// free((*nodes)->options);
			return (1);
		}
		else
			(*nodes)->type = IN_FILE;
		ft_swap_and_null(&(*nodes)->options, i);
		ft_swap_and_null(&(*nodes)->options, i);
	}
	else
	{
		(*nodes)->type = ERROR;
		printf("minishell: syntax error near unexpected token `newline'\n");
		ft_swap_and_null(&(*nodes)->options, i);
	}
	return (0);
}

int	ft_get_out_file2(t_tokens **nodes, int i)
{
	(*nodes)->options[i]++;
	if ((*nodes)->options[i] && (*nodes)->options[i][0] == '>')
	{
		(*nodes)->o_fd = ERROR;
		(*nodes)->type = ERROR;
		// printf("minishell: syntax error near unexpected token `>'\n");
		perror("minishell: syntax error near unexpected token `>'\n");
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
		ft_swap_and_null(&(*nodes)->options, i);
	}
	(*nodes)->options[i]--;
	ft_swap_and_null(&(*nodes)->options, i);
	return (0);
}

int	ft_get_out_file3(t_tokens **nodes, int i)
{
	if ((*nodes)->options[i + 1] && (*nodes)->options[i + 1][0] == '>')
	{
		(*nodes)->type = ERROR;
		(*nodes)->o_fd = ERROR;
		printf("minishell: syntax error near unexpected token `>'\n");
		ft_swap_and_null(&(*nodes)->options, i);
		ft_swap_and_null(&(*nodes)->options, i);
		return (1);
	}
	else if ((*nodes)->options[i + 1])
	{
		if ((*nodes)->o_fd > 0)
			close((*nodes)->o_fd);
		(*nodes)->o_file = (*nodes)->options[i + 1];
		(*nodes)->o_fd = open((*nodes)->options[i + 1], \
							O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if ((*nodes)->o_fd < 0)
		{
			printf("minishell: %s:%s\n", \
				(*nodes)->options[i + 1], strerror(errno));
			(*nodes)->type = ERROR;
		}
		else
			(*nodes)->type = OUT_FILE;
		ft_swap_and_null(&(*nodes)->options, i);
		ft_swap_and_null(&(*nodes)->options, i);
	}
	else
	{
		(*nodes)->type = ERROR;
		(*nodes)->o_fd = ERROR;
		printf("minishell: syntax error near unexpected token `newline'\n");
		ft_swap_and_null(&(*nodes)->options, i);
	}
	return (0);
}
