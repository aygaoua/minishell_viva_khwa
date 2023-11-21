/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:06:30 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/19 18:24:44 by azgaoua          ###   ########.fr       */
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
type == 1 ==>> '<'
type == 2 ==>> '<<'
type == 3 ==>> '>'
type == 4 ==>> '>>'
*/

//----------------------------------STRUCTS----------------------------------//

typedef struct s_node
{
	char		*key;
	char		*value_of_the_key;
	int			plus;
	int			equl;
	struct s_node	*next;
}				t_node;

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
t_tokens		*ft_lstnew(char *str);
char			**ft_s_quots(char *cmd, int *i);
char			**ft_expand_check(t_tokens **cmdline);
void			ft_lstadd_back(t_tokens **lst, t_tokens *new);
void			ft_get_real_args(t_tokens **cmdline);
void			ft_lstdelone(t_tokens *lst, void (*del)(void *));
void			ft_get_in_files(t_tokens **cmdline);
void			ft_get_out_files(t_tokens **cmdline);
void			ft_s_quots_1(char **cmd, char ***s, int *j, int *i);
void			ft_convert_line_1(t_tokens **cmdline, char **s, int *j, \
									int *i);
void			ft_expand_check_1(t_tokens **cmdline, int *i, char ***s, \
									int *j);
int				ft_lstsize(t_tokens *lst);
int				ft_elem_count(char *s, char c);
int				ft_get_cmd_pipe_elems(t_tokens **nodes);
int				ft_get_in_file1(t_tokens **nodes, int i);
int				ft_get_in_file2(t_tokens **nodes, int i);
int				ft_get_in_file3(t_tokens **nodes, int i);
int				ft_infile_while(t_tokens **nodes, int *i);
int				ft_get_out_file1(t_tokens **nodes, int i);
int				ft_get_out_file2(t_tokens **nodes, int i);
int				ft_get_out_file3(t_tokens **nodes, int i);
int				ft_outfile_while(t_tokens **nodes, int *i);
int				ft_quots(t_tokens **cmdline);

//----------------------------------EXECUTION----------------------------------//
t_node			*get_node(t_node **list, char *str);
t_node			**take_env(char **env);
t_node			*ft_lstnew_k(char *env_val);
t_node			*ft_lstlast_k(t_node **lst);
int				delete_line(char **matrix, int row);
int				option(char *str);
int				ft_strcmp(char *s1, char *s2);
int				is_ther_the_win_char(char *str, char c, int len);
int				ft_len(char *str, char c);
int				with_new_line(char **darry, int row);
int				home(t_node **my_env, char *str);
int				arg_path(char *str);
int				ft_lstsize_k(t_node *lst);
void			ft_lstadd_front_k(t_node **lst, t_node *new);
void			my_echo_n(char **argum);
void			ft_lstadd_back_k(t_node **lst, t_node *new);
void			print_list(t_node **list);
void			env_command(char **env);
void			update_env(t_node **my_env);
void			ft_free_list(t_node **list);
void			ft_free_contnue(t_node **lst);
void			cd_command(t_node **env, char **arg);
void			print_oldpwd(t_node **my_env);
void			my_pdw(void);
char			*ft_frontcpy(char *dst, char *src, char del);
char			*go_home(t_node **my_env);
char			*ft_backcpy(char *dst, char *src, char del);


#endif