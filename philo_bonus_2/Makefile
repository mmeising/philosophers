# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 20:04:24 by mmeising          #+#    #+#              #
#    Updated: 2022/04/28 01:09:00 by mmeising         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := gcc
CFLAGS := -Wall -Wextra -Werror -pthread

SRCS :=	\
	exit.c inits.c input.c main.c philo_routine.c sweeper.c time.c utils.c \
	utils2.c watcher.c

OBJ := $(SRCS:%.c=%.o)

HEADER := ./

HEADER_FLAGS := -I $(HEADER)
HEADER_FILES := $(HEADER)philo.h

YELLOW = "\033[33m"
RED = "\033[31m"
GREEN = "\033[32m"
BLUE = "\033[34m"
RESET = "\033[0m"
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

#20 199 100 100 sometimes gets stuck
PHILO_COUNT := 20
DIE_TIME := 500
EAT_TIME := 100
SLEEP_TIME := 100

test: all
	./philo $(PHILO_COUNT) $(DIE_TIME) $(EAT_TIME) $(SLEEP_TIME) 5

debug: fclean
	$(CC) -g $(CFLAGS) $(HEADER_FLAGS) $(SRCS) -o $(NAME)
	lldb $(NAME) $(PHILO_COUNT) $(DIE_TIME) $(EAT_TIME) $(SLEEP_TIME)

.PHONY: all clean fclean re