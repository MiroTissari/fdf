# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 17:40:17 by mtissari          #+#    #+#              #
#    Updated: 2022/05/12 18:44:54 by mtissari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY := all re clean fclean make
CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDES := -I . libft/ minilibx
FILES := main.c display.c colours.c drawer.c map.c utils.c
O_FILES = $(FILES:.c=.o)
LIBFT := libft/
MLX := /usr/local/include
#MLX := minilibx/
MLXFLAGS := /usr/local/lib -lmlx -framework OpenGL -framework AppKit
#MLXFLAGS := minilibx -lmlx -framework OpenGL -framework AppKit
NAME := fdf

#where to find mlx ->		~usr/local/lib/libmlx.a????

#gcc -Wall -Wextra -Werror -Imlx $(FILES) -c -o $@

$(NAME): obj
	@make re -C $(LIBFT)
	@$(CC) $(FLAGS) $(O_FILES) -I $(LIBFT) -I $(MLX) -L $(MLXFLAGS) -L libft/ -lft -o $(NAME)
	
#	$(CC) $(FLAGS) $(O_FILES) -I $(MLX) -L $(MLXFLAGS) -I $(LIBFT) -L $(INCLUDES) -o $(NAME)
#gcc -Wall -Wextra -Werror main.o -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit -o fdf

all: $(NAME)

debug:
	@make re -C $(LIBFT)
	@$(CC) $(FLAGS) -g $(FILES) -I $(LIBFT) -I $(MLX) -L $(MLXFLAGS) -L libft/ -lft -o debug

obj: $(FILES)
	@$(CC) $(CFLAGS) -I $(MLX) $(FILES) -c
#gcc -Wall -Wextra -Werror -Imlx main.c -c -o main.o #

clean:
	rm -f $(O_FILES) 
	make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME) debug
	@make -C $(LIBFT) fclean

re: fclean all
