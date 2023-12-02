/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 03:16:04 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/30 23:17:01 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_get_type(char *line, int *i)
{
	(*i)++;
	if (line[*i - 1] == '\'')
		return (S_QUOT);
	else if (line[*i - 1] == '"')
		return (D_QUOT);
	else if (line[*i - 1] == '>' && line[*i] && line[*i] == '>')
		return ((*i)++, R_APPEND);
	else if (line[*i - 1] == '>')
		return (R_OUT);
	else if (line[*i - 1] == '<' && line[*i] && line[*i] == '<')
		return ((*i)++, R_HERDOC);
	else if (line[*i - 1] == '<')
		return (R_IN);
	else if (line[*i - 1] == '$')
		return (DOLLAR);
	else if (line[*i - 1] == '|')
		return (PIP);
	return (100);
}

int	ft_is_valid_word(char c)
{
	if (c == '\'' || c == '"' || c == '|' || c == '<' || c == '>' \
		|| c == '$' || c == ' ' || c == '\t')
		return (0);
	return (1);
}

char	*ft_get_spcs(char *line, int *i)
{
	int		j;

	j = *i;
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	return (ft_substr(line, j, *i - j));
}

t_token	*ft_lexer(char *line)
{
	int		i;
	int		j;
	t_token	*lst;

	i = 0;
	j = 0;
	lst = NULL;
	if (!line)
		return (NULL);
	while (line[i])
	{
		j = i;
		while (line[i] && ft_is_valid_word(line[i]))
			i++;
		if (i != j)
			ft_lstadd_back2(&lst, ft_lstnew2(ft_substr(line, j, i - j), WORD));
		else if (line[i] == ' ' || line[i] == '\t')
			ft_lstadd_back2(&lst, ft_lstnew2(ft_get_spcs(line, &i), W_SPC));
		else 
			ft_lstadd_back2(&lst, ft_lstnew2(ft_substr(line, i, 1), \
							ft_get_type(line, &i)));
	}
	return (lst);
}
