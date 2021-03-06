# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 22:44:45 by mmeising          #+#    #+#              #
#    Updated: 2022/04/27 00:55:32 by mmeising         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := gcc
CFLAGS := -Wall -Wextra -Werror -pthread

SRCS :=	\
	main.c utils.c utils2.c inits.c philo_routine.c time.c reaper.c exit.c \
	sweeper.c


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

#for some reason die_time = 1 does not work, waits eat_time before dying
PHILO_COUNT := 2
DIE_TIME := 200
EAT_TIME := 100
SLEEP_TIME := 100

test: all
	./philo $(PHILO_COUNT) $(DIE_TIME) $(EAT_TIME) $(SLEEP_TIME)

debug: fclean
	$(CC) -g $(CFLAGS) $(HEADER_FLAGS) $(SRCS) -o $(NAME)
	lldb $(NAME) $(PHILO_COUNT) $(DIE_TIME) $(EAT_TIME) $(SLEEP_TIME)

.PHONY: all clean fclean re
#reaper starts too soon, needs to wait with everything else. or time check is wrong.