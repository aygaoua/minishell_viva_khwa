/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:08:11 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/16 14:45:19 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nbr_of_elem(char *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && \
			s[i + 1] == '>') || (s[i] == '<' && s[i + 1] && \
			s[i + 1] != '<') || (s[i] == '>' && s[i + 1] && \
			s[i + 1] != '>') || s[i] == '|')
			len++;
		i++;
	}
	return (len);
}

char	*ft_convert_line(t_tokens **cmdline)
{
	int		len;
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	len = ft_nbr_of_elem((*cmdline)->input);
	s = malloc (ft_strlen((*cmdline)->input) + (len * 2) + 1);
	// allocation done!!
	while ((*cmdline)->input[i])
	{
		if (s[j] != ' ')
			s[j] = (*cmdline)->input[i];
		else
			s[++j] = (*cmdline)->input[i];
		if (((*cmdline)->input[i] == '<' && \
			(*cmdline)->input[i + 1] == '<') || \
			((*cmdline)->input[i] == '>' && (*cmdline)->input[i + 1] == '>'))
		{
			j++;
			i++;
			s[j] = (*cmdline)->input[i];
		}
		if (((*cmdline)->input[i] && (*cmdline)->input[i + 1] == '>') || \
			((*cmdline)->input[i] && (*cmdline)->input[i + 1] == '<') || \
			((*cmdline)->input[i] == '<' && (*cmdline)->input[i + 1] && \
			(*cmdline)->input[i + 1] != '<') || \
			((*cmdline)->input[i] == '>' && (*cmdline)->input[i + 1] && \
			(*cmdline)->input[i + 1] != '>') || (*cmdline)->input[i] == '|')
		{
			j++;
			s[j] = ' ';
		}
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

int	main(void)
{
	t_tokens	*cmdline;
	char		*str;

	str = NULL;
	cmdline = NULL;
	cmdline = malloc (sizeof(t_tokens));
	if (!cmdline)
		return (0);
	while (0 == 0)
	{
		cmdline->input = readline("minishell-1$ ");
		if (cmdline->input && cmdline->input[0])
		{
			cmdline->cmd = ft_convert_line(&cmdline);
			add_history(cmdline->input);
			cmdline = ft_lstnew(cmdline->cmd);
			ft_get_real_args(&cmdline);
			if (ft_strncmp(cmdline->input, "exit", 5) == 0)
				exit(0);
		}
		else
			continue ;
	}
	return (0);
}
