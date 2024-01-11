# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 18:22:58 by hlabouit          #+#    #+#              #
#    Updated: 2024/01/08 01:06:24 by hlabouit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parsing
CFILES = main.c check_map_errors.c check_map_errors2.c useful_functions.c \
		display_errors.c libft_functions.c libft_functions2.c
COFILES = $(CFILES:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

all: $(NAME)

$(NAME) : $(COFILES) #.h
	@$(CC) $(COFILES) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) $< -c

clean:
	@rm -rf $(COFILES)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re