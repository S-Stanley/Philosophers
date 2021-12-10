# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 23:16:06 by sserbin           #+#    #+#              #
#    Updated: 2021/12/10 19:11:04 by sserbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= 	v2/main.c v2/parsing.c v2/ft_atoi.c v2/exit.c v2/string.c \
		v2/routine.c v2/clean.c v2/setup_philo.c
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