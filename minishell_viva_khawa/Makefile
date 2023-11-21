# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 20:42:57 by azgaoua           #+#    #+#              #
#    Updated: 2023/11/19 18:25:10 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

OBJS = minishell.o ft_lst_tools.o parssing.o parssing1.o \
		quots.o expand.o parssing2.o echo_command.o cd_cmmand1.o cd_command.o \
		env_command.o env_command1.o ft_linked_list.o tools.o pwd_command.o

FILES = minishell.c ft_lst_tools.c parssing.c parssing1.c \
		quots.c expand.c parssing2.c echo_command.c cd_cmmand1.c cd_command.c \
		env_command.c env_command1.c ft_linked_list.c tools.c pwd_command.c

CC = cc

RM = rm -rf

FLGS = -Wall -Wextra -Werror  -fsanitize=address -g3

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