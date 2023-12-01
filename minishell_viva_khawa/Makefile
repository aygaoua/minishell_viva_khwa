# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 20:42:57 by azgaoua           #+#    #+#              #
#    Updated: 2023/12/01 10:49:16 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

OBJS = minishell.o ft_lst_tools.o \
		echo_command.o cd_cmmand1.o cd_command.o \
		env_command.o env_command1.o ft_linked_list.o tools.o pwd_command.o \
		export_command.o export_command1.o export_command2.o export_command3.o \
		export_command4.o unset.o unset1.o find_the_path.o execve.o  \
		lexer.o ft_list_token.o syntax_error.o \
		parcer2.o join_and_split.o pipa.o ft_split.o ft_strdup.o ft_substr.o \
		r_out_file.o r_in_file.o r_heredoc.o parcer.o ft_garbege_clctr.o \
		pip_and_redirection.o syntax_error1.o signal.o

FILES = minishell.c ft_lst_tools.c \
		echo_command.c cd_cmmand1.c cd_command.c \
		env_command.c env_command1.c ft_linked_list.c tools.c pwd_command.c \
		export_command.c export_command1.c export_command2.c export_command3.c \
		export_command4.c unset.c unset1.c find_the_path.c execve.c \
		lexer.c ft_list_token.c syntax_error.c \
		parcer2.c join_and_split.c pipa.c ft_split.c ft_strdup.c ft_substr.c \
		r_out_file.c r_in_file.c r_heredoc.c parcer.c ft_garbege_clctr.c \
		pip_and_redirection.c syntax_error1.c signal.c

CC = cc

RM = rm -rf

FLGS = -Wall -Wextra -Werror #-g3 -fsanitize=address 

all :  $(NAME)

%.o: %.c minishell.h ./libft/*.c ./libft/libft.h
	@$(CC) $(FLGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(NAME) :  $(OBJS) $(FILES)
	@echo "------>making the Minishell<------"
	@cd libft && make && make clean
	@$(CC) $(FLGS) $(OBJS) libft/libft.a -o $(NAME) -lreadline -L$(shell brew --prefix readline)/lib
	@echo "--------->Minishell Done<---------"

clean:
	@echo " clean all the *.o FILES"
	@$(RM) $(OBJS)

fclean:  clean
	@echo " clean --> $(NAME)"
	@$(RM) $(NAME) libft/libft.a

re: fclean all