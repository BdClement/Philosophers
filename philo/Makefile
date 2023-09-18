# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 17:41:26 by clbernar          #+#    #+#              #
#    Updated: 2023/09/18 18:45:04 by clbernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## MAIN VARIABLES

NAME = 			philo

CC = 			cc

CFLAGS = 		-g3 -Wall -Wextra -Werror #-fsanitize=thread

PTHREAD_FLAG = -pthread

RM =			rm -f

RM_RF =			rm -rf

## SOURCES AND LIBS

SRC_DIR = 		./src

SRCS = 			$(SRC_DIR)/main.c\
				$(SRC_DIR)/check_args.c\
				$(SRC_DIR)/init_structs.c\
				$(SRC_DIR)/utils.c\
				$(SRC_DIR)/utils2.c\
				$(SRC_DIR)/clean.c\
				$(SRC_DIR)/routine.c\
				$(SRC_DIR)/dead.c\

## OBJECTS

OBJ_DIR =		./obj

OBJS = 			$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

## HEADERS

HDIR = 			./inc

HD = 			$(HDIR)/philo.h

INC_HD =		-I $(HDIR)

## RULES

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(INC_HD) $(OBJS) $(PTHREAD_FLAG) -o $@

$(OBJS):		$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HD)
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) $(INC_HD) -c $< -o $@

clean:
				$(RM_RF) $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY: 		all clean fclean re
