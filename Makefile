# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 14:24:42 by ahmaymou          #+#    #+#              #
#    Updated: 2023/03/05 19:54:40 by ahmaymou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS_OBJ = $(shell ls | grep .c | grep -v main)

SRC = main.c

TO_INSTALL = $(shell brew --prefix readline | grep "Error")
OS = $(shell uname)

ifeq ($(TO_INSTALL),Error)
	$(shell brew install readline)
endif

ifeq ($(OS),Darwin)
	READLINE_INC = -I $(shell brew --prefix readline)/include
	READLINE_LIB = -L $(shell brew --prefix readline)/lib
endif

FLAGS = -Wall -Werror -Wextra

CC = cc

LIB = libft/libft.a

OBJ = $(SRCS_OBJ:.c=.o)


all : $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) $(READLINE_INC) -c $< -o $@

$(NAME) : $(OBJ) minishell.h main.c
	make -C libft/
	$(CC) $(FLAGS) $(SRC) $(OBJ) $(LIB) -lreadline $(READLINE_LIB) -o $(NAME)
	@rm -rf $(LIBS)

clean :
	make clean -C libft
	rm -rf $(OBJ)
fclean : clean
	make fclean -C libft
	rm -rf $(LIBS) $(NAME)

re : fclean all

.PHONY : all clean fclean re