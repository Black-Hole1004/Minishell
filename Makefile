# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 14:24:42 by ahmaymou          #+#    #+#              #
#    Updated: 2023/03/22 19:03:46 by ahmaymou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

Color_Off=\033[0m
LIGHTRED=\033[1;31m
Blue=\033[0;34m
LightBlue=\033[1;34m
Purple=\033[0;35m
LightPurple=\033[1;35m
Cyan=\033[0;36m
Light Cyan=\033[1;36m
OKBLUE = \033[94m
OKCYAN = \033[96m
OKGREEN = \033[92m

BANNER=\
'   ▄▄▄▄███▄▄▄▄     ▄█  ███▄▄▄▄     ▄█     ▄████████    ▄█    █▄       ▄████████   ▄█        ▄█       '\
' ▄██▀▀▀███▀▀▀██▄  ███  ███▀▀▀██▄  ███    ███    ███   ███    ███     ███    ███  ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███▌   ███    █▀    ███    ███     ███    █▀   ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄      ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀      ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███           ███   ███    ███     ███    █▄   ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███     ▄█    ███   ███    ███     ███    ███  ███▌    ▄ ███▌    ▄ '\
'  ▀█   ███   █▀   █▀    ▀█   █▀   █▀    ▄████████▀    ███    █▀      ██████████  █████▄▄██ █████▄▄██ '\
'                                                                            ▀         ▀         	  '
                                                                                                     

SRCS_OBJ = $(shell ls *.c | grep -v minishell_main.c) $(shell ls builtin_functions/*.c ) $(shell ls execution/*.c | grep -v mainex.c)

SRC = minishell_main.c

FLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

CC = cc

LIBS = libft/libft.a libftprintf.a

OS = $(shell uname)

ifeq ($(OS),Darwin)
	READLINE_INC = -I $(shell brew --prefix readline)/include
	READLINE_LIB = -L $(shell brew --prefix readline)/lib
endif

echo2 = @echo "\033[36m \n\nMINISHELL is ready !!! :) \033[m\n\n"
echo3 = @echo "\033[31mMINISHELL Objects removed successfully !!! :) \033[m"
echo4 = @echo "\033[31mMINISHELL removed successfully !!! :) \033[m"

OBJ = $(SRCS_OBJ:.c=.o)

all : banner2 libftprintf $(NAME)

banner2:
	@clear
	@echo "\n"
	@echo "$(LightPurple)"
	@for s in $(BANNER) ; do \
		printf "%s\n" "$$s" ; \
		sleep 0.03 ; \
	done ; \
	echo "$(LIGHTRED)                     Copyright : Black-Hole1004, Abdellrabiai :) \n$(Color_Off)"
%.o: %.c minishell.h
	@printf "$(LIGHTRED) Generating minishell objects... %-33.33s\r" $@
	@$(CC) $(FLAGS) $(READLINE_INC) -c $< -o $@

$(NAME) : $(OBJ) execution/mainex.c minishell.h
	@$(CC) $(FLAGS) $(SRC) execution/mainex.c $(OBJ) $(LIBS) -lreadline $(READLINE_LIB) -o $(NAME)
	$(echo2)

libftprintf :
	@make bonus -C libft/
	@make -C ft_printf/

clean :
	@make clean -C libft
	@make clean -C ft_printf
	@rm -rf $(OBJ)
	$(echo3)

fclean : clean
	@rm -rf $(LIBS) $(NAME)
	@rm -rf *.dSYM .vscode
	$(echo4)

re : fclean all

.PHONY : all clean fclean re