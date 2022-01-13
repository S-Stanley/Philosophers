# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 23:16:06 by sserbin           #+#    #+#              #
#    Updated: 2022/01/13 18:15:24 by sserbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= 	src/main.c src/parsing.c src/ft_strlen.c src/fork.c src/ft_atoi.c src/one_philo.c
OBJS=$(SRCS:.c=.o)
NAME = philo
CC = clang
FLAGS = -Wall -Wextra -Werror -pthread -g
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
