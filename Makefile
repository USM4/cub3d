CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
NAME = cub
GREEN = \033[32m
COLOR_OFF = \033[0m
SOURCES = ./src/main.c ./src/utils.c ./src/utils2.c
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