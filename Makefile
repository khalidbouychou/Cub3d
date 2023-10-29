# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 18:28:45 by khbouych          #+#    #+#              #
#    Updated: 2023/10/29 17:36:10 by khbouych         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADERS = headers/cub.h headers/get_next_line.h
FLAGS = gcc -Wall -Wextra -Werror #-g -fsanitize=address

#FLAG_MLX = -Lmlx -lmlx -framework OpenGL -framework IOkit -lglfw
#INCLUDE = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
#LIB = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib
#MLX = MLX42/build/libmlx42.a
OBJ_DIR = src/objs
DIR_SRC = src

FSRCS = $(wildcard $(DIR_SRC)/*.c)

OBJS =  $(patsubst $(DIR_SRC)/%.c,$(OBJ_DIR)/%.o,$(FSRCS))

all: creat_dir $(NAME)

$(NAME): $(OBJS)
	@$(FLAGS) $(FLAG_MLX) $(OBJS) $(MLX) $(LIB) $(INCLUDE)-o $(NAME)

$(OBJ_DIR)/%.o: $(DIR_SRC)/%.c $(HEADERS)
	@$(FLAGS) -c $< -o $@
	@echo "compiled -- [$<] -- successfully!"

creat_dir:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "clean successfully!"

fclean: clean
	@rm -rf $(NAME)
	@echo "[cub3D] deleted successfully!"

re: fclean all

.PHONY: all clean fclean re