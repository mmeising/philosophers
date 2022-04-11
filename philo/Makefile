# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 15:31:56 by mmeising          #+#    #+#              #
#    Updated: 2022/04/11 15:42:22 by mmeising         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := gcc
CFLAGS := -Wall -Wextra -Werror

SRCS :=	\
	main.c

OBJ := $(SRCS:%.c=%.o)

HEADER := ./

HEADER_FLAGS := -I $(HEADER)
HEADER_FILES := $(HEADER)philo.h

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(HEADER_FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER_FILES)
	@echo Compiling $@
	@$(CC) $(CFLAGS) $(HEADER_FLAGS) -c $< -o $@
	@echo Finished compiling $@

clean:
	@echo Cleaning...
	@rm -rf $(OBJ)
	@printf $(UP)$(CUT)
	@echo Cleaned object files!

fclean: clean
	@echo Cleaning...
	@rm -f $(NAME)
	@printf $(UP)$(CUT)
	@echo Cleaned library file!

re: fclean all

.PHONY: all clean fclean re