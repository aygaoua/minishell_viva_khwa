/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:08:11 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/23 04:31:11 by azgaoua          ###   ########.fr       */
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
			s[i + 1] != '>') || s[i] == '|' || s[i] == '\'')
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
	s = malloc (ft_strlen((*cmdline)->input) + ((len +  1) * 2));
	while ((*cmdline)->input[i])
	{
		ft_convert_line_1(cmdline, &s, &j, &i);
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

void	ft_convert_line_1(t_tokens **cmdline, char **s, int *j, int *i)
{
	if ((*s)[*j] != ' ')
		(*s)[*j] = (*cmdline)->input[*i];
	else
		(*s)[++(*j)] = (*cmdline)->input[*i];
	if (((*cmdline)->input[*i] == '<' && \
		(*cmdline)->input[*i + 1] == '<') || \
		((*cmdline)->input[*i] == '>' && (*cmdline)->input[*i + 1] == '>'))
	{
		(*j)++;
		(*i)++;
		(*s)[*j] = (*cmdline)->input[*i];
	}
	if (((*cmdline)->input[*i] && (*cmdline)->input[*i + 1] == '>') || \
		((*cmdline)->input[*i] && (*cmdline)->input[*i + 1] == '<') || \
		((*cmdline)->input[*i] == '<' && (*cmdline)->input[*i + 1] && \
		(*cmdline)->input[*i + 1] != '<') || \
		((*cmdline)->input[*i] == '>' && (*cmdline)->input[*i + 1] && \
		(*cmdline)->input[*i + 1] != '>') || (*cmdline)->input[*i] == '|')
	{
		(*j)++;
		(*s)[*j] = ' ';
	}
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_tokens	*cmdline;
	t_node **kmi = take_env (env);/*this is mo7a O 7madd speaking*/
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
			printf ("---1----> %s <--------\n", (cmdline)->cmd);
			cmdline = ft_lstnew(cmdline->cmd);
			ft_get_real_args(&cmdline);
			if (ft_strncmp(cmdline->input, "exit", 5) == 0)
				exit(0);
			else if (ft_strncmp(cmdline->input, "echo", 4) == 0)
				my_echo_n((cmdline->options + 1));
			else if (ft_strncmp(cmdline->input, "cd", 2) == 0)
				cd_command (take_env (env), cmdline->options + 1);
			else if (ft_strncmp(cmdline->input, "pwd", 3) == 0)
				my_pdw();
/*#######################this is mo7a O 7madd speaking########################*/
			else if (ft_strncmp(cmdline->input, "export", 6) == 0)
			{
				// t_node **kmi = take_env (env);
				printf ("THIS IS EXPORT%p\n",cmdline->options + 2);
				export_command (kmi, cmdline->options + 1);
				// export_command (take_env (env), NULL);
				print_export (kmi);
			}
			else if (ft_strncmp(cmdline->input, "unset", 5) == 0)
			{
				printf ("THIS IS UNSET\n");
				unset_command (kmi, cmdline->options + 1);
				// if (kmi)
					print_export (kmi);
			}
			else if (ft_strncmp(cmdline->input, "env", 3) == 0)
			{
				printf ("THIS IS ENV\n");
				env_command(env);
			}
			else
				let_exec_command (find_path (get_node (kmi , "PATH")), cmdline->options, make_list_arr (kmi));
/*#######################this is mo7a O 7madd speaking########################*/
		}
		else
			continue ;
	}
	return (0);
}
