# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 18:28:45 by khbouych          #+#    #+#              #
#    Updated: 2023/11/25 21:56:33 by khbouych         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADERS = headers/cub.h headers/get_next_line.h
FLAGS = gcc  -Wall -Wextra -Werror #-g -fsanitize=address

FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw

INCLUDE = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
LIB = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib
MLX = MLX42/build/libmlx42.a

git_msg = still parsing color

PSRC=src/parsing/ft_split.c src/parsing/ft_strncmp.c src/parsing/o_list.c src/parsing/o_map.c\
src/parsing/outils_.c src/parsing/outils.c src/parsing/p_map.c src/parsing/p_textures1.c\
src/parsing/p_textures2.c src/parsing/par1.c  src/main.c src/mlx.c src/o_color.c src/o_map1.c src/raycasting.c\
src/parsing/get_next_line_utils.c \
src/parsing/get_next_line.c \
src/parsing/p_map1.c \
src/parsing/p_map2.c \

POBJ= $(PSRC:.c=.o)

all: $(NAME)
	@echo "\033[0;32m[------ Compilation done -------]\033[0m"

$(NAME): $(POBJ)
	@echo "\033[0;32m[------ Compiling -----] $(NAME)\033[0m"
	@$(FLAGS) $(FLAG_MLX) $(POBJ)  $(MLX) $(LIB) $(INCLUDE) -o $(NAME)

%.o: %.c $(HEADERS)
	@echo "\033[0;32m[------ Compiling -----] $(NAME) File \033[0m"
	@$(FLAGS) $(INCLUDE) -c $< -o $@

git:
	make fclean
	git add .
	git commit -m "$(git_msg)"
	git status
	git push
clean:
	@echo "\033[0;31m[------ Cleaning -----]  $(POBJ)\033[0m"
	@rm -fr  $(POBJ)

fclean:
	@echo "\033[0;31m[---- Cleaning -----] $(NAME)  $(POBJ)\033[0m"
	@echo "\033[0;31m[---- Cleaning -----]  $(POBJ)\033[0m"
	@rm -fr  $(POBJ) $(NAME)

re : fclean all
.PHONE: all clean fclean re