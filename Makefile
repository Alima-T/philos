# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 15:41:20 by aokhapki          #+#    #+#              #
#    Updated: 2024/12/06 19:12:45 by aokhapki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philos
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -Ilibft -pthread
#INCLUDE			= -lpthread: Links the pthread library, making the pthread functions available during the linking stage. 
RM				= rm -f

SRCS =			philo.c 
				
LIBFT_DIR = ./LIBFT
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
