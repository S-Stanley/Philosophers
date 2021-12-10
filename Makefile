# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 23:16:06 by sserbin           #+#    #+#              #
#    Updated: 2021/12/10 18:31:18 by sserbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= 	v2/main.c
OBJS=$(SRCS:.c=.o)
NAME = philo
CC = clang
FLAGS = -Wall -Wextra -Werror -pthread -fsanitize=address
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