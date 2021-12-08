# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 23:16:06 by sserbin           #+#    #+#              #
#    Updated: 2021/12/08 21:49:08 by sserbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= main.c src/exit.c src/string.c src/ft_atoi.c src/parsing.c
OBJS=$(SRCS:.c=.o)
NAME = philo
CC = clang
FLAGS = -Wall -Wextra -Werror
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