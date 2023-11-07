/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:06:30 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/07 17:06:00 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "./libft/libft.h"

# define ERROR		-2
# define IN_FILE	1
# define IN_HERDOC	2
# define OUT_FILE	3
# define OUT_APPEND	4

/*
type_r == 1 ==>> '<'
type_r == 2 ==>> '<<'
type_r == 3 ==>> '>'
type_r == 4 ==>> '>>'
*/

//----------------------------------STRUCTS----------------------------------//
typedef struct s_tokens
{
	char			*input;
	char			*cmd;
	char			**options;
	char			*i_file;
	char			*o_file;
	char			*dlmtr;
	int				i_fd;
	int				o_fd;
	int				type;
	struct s_tokens	*next;
}					t_tokens;

//---------------------------------PARSSING----------------------------------//
t_tokens		*ft_lstlast(t_tokens *lst);
void			ft_lstclear(t_tokens **lst);
t_tokens		*ft_lstnew(char *str);
void			ft_lstadd_back(t_tokens **lst, t_tokens *new);
void			ft_get_real_args(t_tokens **cmdline);
void			ft_lstdelone(t_tokens *lst, void (*del)(void *));
void			ft_get_in_files(t_tokens **cmdline);
void			ft_get_out_files(t_tokens **cmdline);
int				ft_lstsize(t_tokens *lst);
int				ft_get_cmd_pipe_elems(t_tokens **nodes);
int				ft_get_in_file1(t_tokens **nodes, int i);
int				ft_get_in_file2(t_tokens **nodes, int i);
int				ft_get_in_file3(t_tokens **nodes, int i);
int				ft_infile_while(t_tokens **nodes, int *i);
int				ft_get_out_file1(t_tokens **nodes, int i);
int				ft_get_out_file2(t_tokens **nodes, int i);
int				ft_get_out_file3(t_tokens **nodes, int i);
int				ft_outfile_while(t_tokens **nodes, int *i);

#endif