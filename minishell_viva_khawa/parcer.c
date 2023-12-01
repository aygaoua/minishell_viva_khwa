/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:01:31 by azgaoua           #+#    #+#             */
/*   Updated: 2023/12/01 14:16:15 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_to_search(t_token *lst)
{
	int	i;

	i = 0;
	if (lst && (lst->type == WORD \
		&& (lst->value[0] == '_' || ft_isalpha(lst->value[0]))))
		return (1);
	return (0);
}

int	ft_len_var(char *s)
{
	int	j;

	j = 0;
	if (s[0] == '?')
		return (1);
	while (s[j] && (s[j] == '_' || ft_isalpha(s[j]) \
			|| ft_isdigit(s[j])))
		j++;
	return (j);
}

void	ft_execute_moha(t_tokens *cmdline, t_node **kmi)
{
	char	**env;

	env = make_list_arr (kmi);
	if (ft_lstsize_token(cmdline) == 2)
	{
		if (build(cmdline->next->input) != 0)
			excut_biltins(build(cmdline->next->input), kmi, cmdline);
		else
			let_exec_command(find_path(get_node (kmi, "PATH")), \
								cmdline->options, env);
	}
	else if (ft_lstsize_token(cmdline) > 2)
	{
		bipa(&cmdline->next, kmi, env);
		ft_free_matrix_contnt (env);
	}
}
