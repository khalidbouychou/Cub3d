# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 18:28:45 by khbouych          #+#    #+#              #
#    Updated: 2023/10/30 15:43:39 by khbouych         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADERS = headers/cub.h headers/get_next_line.h
FLAGS = gcc -Wall -Wextra -Werror #-g -fsanitize=address

FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw

INCLUDE = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
LIB = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib
MLX = MLX42/build/libmlx42.a


SRC= src/free.c \
	src/ft_split.c \
	src/get_next_line_utils.c \
	src/get_next_line.c \
	src/o_list.c \
	src/main.c \
	src/outils_.c \
	src/outils.c \
	src/p_map.c \
	src/p_textures1.c \
	src/p_textures2.c \
	src/mlx.c \

OBJ= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(FLAGS) $(FLAG_MLX) $(OBJ) $(MLX) $(LIB) $(INCLUDE) -o $(NAME)

%.o: %.c $(HEADERS)
	$(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -fr $(OBJ)

fclean:
	rm -fr $(OBJ) $(NAME)

re : fclean all
.PHONE: all clean fclean re