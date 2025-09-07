# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuwu <yuwu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 16:36:29 by yuwu              #+#    #+#              #
#    Updated: 2025/09/07 17:49:10 by yuwu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
HEADERS := include/philo.h
CFLAGS := -Wall -Wextra -Werror -Iinclude
CC := cc

SRC_DIR := src
OBJ_DIR := obj

# Sources
SRCS := $(SRC_DIR)/preparsing.c $(SRC_DIR)/parsing.c \
		$(SRC_DIR)/utils.c $(SRC_DIR)/routine.c $(SRC_DIR)/philo.c

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR) 
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re			
