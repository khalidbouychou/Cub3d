# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 18:28:45 by khbouych          #+#    #+#              #
#    Updated: 2023/10/18 19:40:13 by khbouych         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADERS = headers/cub.h headers/get_next_line.h
FLAGS = gcc -Wall -Wextra -Werror

OBJ_DIR = src/objs
DIR_SRC = src

FSRCS = $(wildcard $(DIR_SRC)/*.c)

OBJS =  $(patsubst $(DIR_SRC)/%.c,$(OBJ_DIR)/%.o,$(FSRCS))

all: creat_dir $(NAME)

$(NAME): $(OBJS)
	@$(FLAGS) $(OBJS) -o $(NAME)

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