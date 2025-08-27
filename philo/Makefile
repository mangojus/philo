# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rshin <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 09:17:03 by rshin             #+#    #+#              #
#    Updated: 2025/08/27 15:49:36 by rshin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread

IFLAGS = -I $(INC_D) -MMD -MP

SRC = $(SRC_D)/main.c \
	  $(SRC_D)/init.c \
	  $(SRC_D)/run.c \
	  $(SRC_D)/thread_utils.c \
	  $(SRC_D)/action.c \
	  $(SRC_D)/clean.c \
	  $(SRC_D)/utils.c 

OBJ = $(patsubst $(SRC_D)/%.c, $(BLD_D)/%.o, $(SRC))

DEP = $(patsubst $(SRC_D)/%.c, $(BLD_D)/%.d, $(SRC))

SRC_D = src

BLD_D = .build

INC_D = include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $(NAME)

$(BLD_D)/%.o: $(SRC_D)/%.c Makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(BLD_D) $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
