/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:06:30 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/05 16:22:18 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>
#include <readline/history.h>
#include <readline/readline.h>
# include "./libft/libft.h"

# define error      -2
# define in_file    1
# define in_heredoc 2
# define out_file   3
# define out_append 4

/*
type_r == 1 ==>> '<'
type_r == 2 ==>> '<<'
type_r == 3 ==>> '>'
type_r == 4 ==>> '>>'
*/

//----------------------------------STRUCTS----------------------------------//
typedef struct s_tokens
{
	char            *input;
	char            *cmd;
	char            **options;
	char            *i_file;
	char            *o_file;
	char            *dlmtr;
	int             i_fd;
	int             o_fd;
	int             type;
	struct s_tokens  *next;
}                   t_tokens;



//---------------------------------PARSSING----------------------------------//
void			ft_lstadd_back(t_tokens **lst, t_tokens *new);
void			ft_get_real_args(t_tokens **cmdline);
void			ft_lstdelone(t_tokens *lst, void (*del)(void *));
void			ft_get_in_file(t_tokens **cmdline);
int				ft_lstsize(t_tokens *lst);
t_tokens		*ft_lstlast(t_tokens *lst);
t_tokens		*ft_lstnew(char *str);
int				ft_get_in_file1(t_tokens **nodes, int i);
int				ft_get_in_file2(t_tokens **nodes, int i);
int				ft_get_in_file3(t_tokens **nodes, int i);
int				ft_infile_while(t_tokens **nodes, int *i);

#endif