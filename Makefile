# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 11:37:07 by bgazur            #+#    #+#              #
#    Updated: 2025/06/27 09:43:09 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		pipex
CC =		cc
CFLAGS =	-Wall -Werror -Wextra
RM =		rm -f

INC_DIR =	include
OBJ_DIR =	objects
SRC_DIR =	src

HDR =		$(INC_DIR)/pipex.h

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)

SRC =		errors.c \
			execution.c \
			ft_split_utils.c \
			ft_split.c \
			main.c \
			redirection.c \
			utils.c

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ_DIR) $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
