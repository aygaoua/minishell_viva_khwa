# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 20:42:57 by azgaoua           #+#    #+#              #
#    Updated: 2023/10/30 22:19:33 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

OBJS = minishell.o ft_lst_tools.o parssing.o

FILES = minishell.c ft_lst_tools.c parssing.c

CC = cc

RM = rm -rf

FLGS = -Wall -Wextra -Werror -g3 -fsanitize=address

all :  $(NAME)

%.o: %.c minishell.h ./libft/*.c ./libft/libft.h
	$(CC) $(FLGS)  -c $< -o $@

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