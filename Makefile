# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 17:40:17 by mtissari          #+#    #+#              #
#    Updated: 2022/06/17 12:37:56 by mtissari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY := all re clean fclean make
CC := gcc
CFLAGS := -Wall -Wextra -Werror
FILES := main.c display.c colours.c drawer.c map.c utils.c keyboard.c mouse.c \
		helpers.c colours2.c
SOURCES := $(addprefix sources/, $(FILES))
O_FILES = $(FILES:.c=.o)
LIBFT := libft/
MLX := /usr/local/include
MLXFLAGS := /usr/local/lib -lmlx -framework OpenGL -framework AppKit
NAME := fdf

$(NAME):
	@make andclean -C $(LIBFT)
	@$(CC) $(FLAGS) $(SOURCES) -I $(LIBFT) -I $(MLX) -L $(MLXFLAGS) -L libft/ -lft -o $(NAME)

debug:
	@make re -C $(LIBFT)
	@$(CC) $(FLAGS) -g $(SOURCES) -I $(LIBFT) -I $(MLX) -L $(MLXFLAGS) -L libft/ -lft -o debug

all: $(NAME)

clean:
	@rm -f debug
	@make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all
