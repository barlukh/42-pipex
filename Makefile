# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 11:37:07 by bgazur            #+#    #+#              #
#    Updated: 2025/06/18 11:38:45 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		pipex
BONUS =		pipex_bonus
CC = 		cc
CFLAGS =	-Wall -Werror -Wextra
RM = 		rm -f

HDR =		pipex.h
HDR_B =		pipex_bonus.h

OBJ_DIR = 	objects
OBJ_DIR_B =	objects_b

OBJS =		$(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_B =	$(SRCS_B:%.c=$(OBJ_DIR_B)/%.o)

SRCS = 		main.c

SRCS_B = 	main.c

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BONUS): $(OBJ_DIR_B) $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(BONUS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_B):
	mkdir -p $(OBJ_DIR_B)

$(OBJ_DIR)/%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_B)/%.o: %.c $(HDR) $(HDR_B)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ_DIR) $(OBJ_DIR_B) $(NAME) $(BONUS)

bonus: $(OBJ_DIR_B) $(BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
