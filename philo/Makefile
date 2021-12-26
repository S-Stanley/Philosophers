# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 23:16:06 by sserbin           #+#    #+#              #
#    Updated: 2021/12/26 17:27:49 by sserbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= 	main.c \
		src/routine.c src/parsing.c src/setup_philo.c src/fork.c \
		utils/clean.c utils/exit.c utils/ft_atoi.c utils/ft_strlen.c utils/print_str.c \
		utils/time_management.c utils/give_name.c
OBJS=$(SRCS:.c=.o)
NAME = philo
CC = clang
FLAGS = -Wall -Wextra -Werror -pthread # -g -fsanitize=address
RM = rm -rf

all: $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re