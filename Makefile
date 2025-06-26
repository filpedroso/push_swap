# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpedroso <fpedroso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 18:27:51 by filpedroso        #+#    #+#              #
#    Updated: 2025/06/26 19:56:09 by fpedroso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compilation Variables
NAME = push_swap
BONUS = checker
CC = cc
CFLAGS = -Wextra -Wall -Werror -g


# Source files
SRC_MAIN = src/push_swap_main.c
FILES =		src/push_swap.c									\
			src/best_plan_ab.c		src/load_stack.c		\
			src/execute_plan.c		src/min_rotations.c		\
			src/libft_tools.c		src/moves_1.c			\
			src/moves_2.c			src/stack_tools.c		\
			src/push_back.c			src/args_to_str.c

F_BONUS =	bonus/checker_main.c	bonus/checker.c			\
			bonus/get_next_line.c


# Object files
OBJ = $(SRC_MAIN:.c=.o) $(FILES:.c=.o)
OBJ_B = $(FILES:.c=.o) $(F_BONUS:.c=.o)


# Verbose flag
VB	= 0
ifeq ($(VB),1)
	AT =
else
	AT = @
endif


# Colors
BLACK	= \033[1;30m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
MAGENTA	= \033[1;35m
CYAN	= \033[1;36m
WHITE	= \033[1;37m
NC		= \033[0m


# Rules
%.o: %.c
	$(AT) $(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(AT) $(CC) $(CFLAGS) -o $@ $^
	@printf "$(CYAN)push_swap compiled.\n"

$(BONUS): $(OBJ_B)
	$(AT) $(CC) $(CFLAGS) -o $@ $^
	@printf "$(CYAN)checker compiled.\n"


all: $(NAME) $(BONUS)

bonus: $(BONUS)


clean:
	$(AT) rm -f $(OBJ) $(OBJ_B)
	@printf "$(BLACK)object files deleted.\n"

fclean: clean
	$(AT) rm -f $(NAME) $(BONUS)
	@printf "$(RED)executables deleted.\n"

re: fclean all

.PHONY: all bonus clean fclean re
