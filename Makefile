# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 22:21:54 by hlabouit          #+#    #+#              #
#    Updated: 2024/01/16 23:03:54 by hlabouit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast #-fsanitize=address -g -O3
NAME = cub
GREEN = \033[32m
COLOR_OFF = \033[0m
SOURCES = ./src/main.c ./src/parsing/check_map_errors.c ./src/parsing/check_map_errors2.c ./src/parsing/check_map_errors3.c ./src/parsing/useful_functions.c \
		./src/parsing/check_map_errors4.c ./src/parsing/display_errors.c ./src/parsing/libft_functions.c ./src/parsing/libft_functions2.c \
		./src/parsing/libft_functions3.c ./src/utils/utils.c ./src/utils/utils2.c ./src/utils/inits.c \
		./src/raycasting/raycasting_utils.c \
		./src/raycasting/raycasting_utils2.c ./src/raycasting/raycasting.c ./src/textures/textures.c ./src/move_events/drawing.c \
		./src/move_events/events.c 
INCLUDES =  ./includes/cub3d.h
OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o : %.c $(INCLUDES)
	@printf "${GREEN}Compiling $<... ${COLOR_OFF}\r"
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean :
	@rm -f $(OBJECTS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: fclean clean re all