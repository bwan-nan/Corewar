# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 17:34:44 by fdagbert          #+#    #+#              #
#    Updated: 2019/07/03 01:21:58 by fdagbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_PATH = src
FUNCTIONS = ft_bzero.c			\
			ft_memset.c			\
			ft_memmove.c		\
			ft_strlen.c			\
			ft_wcslen.c			\
			ft_islower.c		\
			ft_isdigit.c		\
			ft_toupper.c		\
			ft_atoi.c			\
			ft_atoim.c			\
			ft_strupcase.c		\
			ft_strcat.c			\
			ft_strncat.c		\
			ft_strcpy.c			\
			ft_strncpy.c		\
			ft_strnew.c			\
			ft_strchr.c			\
			ft_strjoin.c		\
			ft_strcmp.c			\
			ft_str_is_numeric.c	\
			ft_get_next_line.c	\
			ft_break.c			\
			ft_ceil.c
SRC = $(addprefix $(SRC_PATH)/, $(FUNCTIONS))

OBJ_PATH = object
OBJ_SRC = $(FUNCTIONS:.c=.o)
OBJECTS = $(addprefix $(OBJ_PATH)/, $(OBJ_SRC))

INC_PATH = include
INC_SRC = $(INC_PATH)/libft.h				\
			$(INC_PATH)/ft_get_next_line.h

INC_CC = -I$(INC_PATH)

CC = gcc
CFLAGS = -Wall -Werror -Wextra

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC_SRC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) -g $(CFLAGS) $(INC_CC) -o $@ -c $<

clean:
	@rm -fv $(OBJECTS)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -fv $(NAME)

re: fclean all
