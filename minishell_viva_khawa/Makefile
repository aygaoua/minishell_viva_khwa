# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 20:42:57 by azgaoua           #+#    #+#              #
#    Updated: 2023/11/30 09:18:45 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

OBJS = minishell.o ft_lst_tools.o \
		expand.o echo_command.o cd_cmmand1.o cd_command.o \
		env_command.o env_command1.o ft_linked_list.o tools.o pwd_command.o \
		export_command.o export_command1.o export_command2.o export_command3.o \
		export_command4.o unset.o unset1.o find_the_path.o execve.o split_p.o \
		lexer.o ft_list_token.o syntax_error.o \
		parcer2.o join_and_split.o pipa.o

FILES = minishell.c ft_lst_tools.c \
		expand.c echo_command.c cd_cmmand1.c cd_command.c \
		env_command.c env_command1.c ft_linked_list.c tools.c pwd_command.c \
		export_command.c export_command1.c export_command2.c export_command3.c \
		export_command4.c unset.c unset1.c find_the_path.c execve.c split_p.c \
		lexer.c ft_list_token.c syntax_error.c \
		parcer2.c join_and_split.c pipa.c

CC = cc

RM = rm -rf

FLGS = -Wall -Wextra -Werror #-g -fsanitize=address 

all :  $(NAME)

%.o: %.c minishell.h ./libft/*.c ./libft/libft.h
	@$(CC) $(FLGS)  -c $< -o $@

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