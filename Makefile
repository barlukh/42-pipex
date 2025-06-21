# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 11:37:07 by bgazur            #+#    #+#              #
#    Updated: 2025/06/21 11:05:00 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		pipex
BONUS =		pipex_bonus
CC =		cc
CFLAGS =	-Wall -Werror -Wextra
RM =		rm -f

INC_DIR =	include
OBJ_DIR =	objects
OBJ_DIR_B =	objects_b
SRC_DIR =	src

HDR =		$(INC_DIR)/pipex.h
HDR_B =		$(INC_DIR)/pipex_bonus.h

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_B =		$(SRC_B:%.c=$(OBJ_DIR_B)/%.o)

SRC =		cleanup.c \
			errors.c \
			ft_putstr.c \
			ft_split_utils.c \
			ft_split.c \
			main.c \
			processes.c

SRC_B =		main.c

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BONUS): $(OBJ_DIR_B) $(OBJ_B)
	$(CC) $(CFLAGS) $(OBJ_B) -o $(BONUS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_B):
	mkdir -p $(OBJ_DIR_B)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_B)/%.o: $(SRC_DIR)/%.c $(HDR) $(HDR_B)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ_DIR) $(OBJ_DIR_B) $(NAME) $(BONUS)

bonus: $(OBJ_DIR_B) $(BONUS)

clean:
	$(RM) $(OBJ) $(OBJ_B)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
