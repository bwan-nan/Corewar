# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 17:34:44 by fdagbert          #+#    #+#              #
#    Updated: 2019/07/18 01:13:37 by fdagbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_COR = corewar

SRC_PATH = src
LIB_PATH = lib
OBJ_PATH = object
INC_PATH = include

LIB_NAME = libftprintf.a
LIBFT_NAME = libft.a

# CHROME = /Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome
# CHROMIUM = /usr/bin/chromium-browser

LIBFT_PATH = $(LIB_PATH)/libft
FTPRINTF_PATH = $(LIB_PATH)/ft_printf

SRC_COR_PATH = $(SRC_PATH)/$(NAME_COR)
COR_FCT = op.c						\
		  ft_test_atoi_base.c		\
		  ft_champion_parser.c		\
		  ft_end.c					\
		  ft_clean.c				\
		  main.c
COR_SRC = $(addprefix $(SRC_COR_PATH)/,$(COR_FCT))

OBJ_COR_PATH = $(OBJ_PATH)/$(NAME_COR)
OBJ_COR = $(COR_FCT:.c=.o)
OBJ_COR_SRC = $(addprefix $(OBJ_COR_PATH)/,$(OBJ_COR))

OBJECTS = $(OBJ_COR_SRC)

HEAD_SRC = $(LIBFT_PATH)/$(INC_PATH)/libft.h				\
		   $(LIBFT_PATH)/$(INC_PATH)/ft_get_next_line.h		\
		   $(FTPRINTF_PATH)/$(INC_PATH)/ft_printf.h			\
		   $(INC_PATH)/op.h									\
		   $(INC_PATH)/corewar.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L$(LIB_PATH)/ft_printf
LDLIBS = -lftprintf

INCLUDES = $(LIBFT_PATH)/$(INC_PATH) $(FTPRINTF_PATH)/$(INC_PATH) $(INC_PATH)
INC_CC = $(foreach DIR,$(INCLUDES),-I$(DIR))

.PHONY: all, clean, fclean, re, lib

all:
	@$(MAKE) $(NAME_COR)

$(NAME_COR): $(LIBFT_PATH)/$(LIBFT_NAME) $(FTPRINTF_PATH)/$(LIB_NAME) $(OBJECTS)
	$(CC) -o $(NAME_COR) $(OBJECTS) $(INC_CC) $(LDFLAGS) $(LDLIBS)

$(OBJ_COR_PATH)/%.o: $(SRC_COR_PATH)/%.c $(HEAD_SRC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_COR_PATH) 2> /dev/null || true
	$(CC) -g $(CFLAGS) $(INC_CC) -o $@ -c $<

$(LIBFT_PATH)/$(LIBFT_NAME): lib

lib:
	@$(MAKE) -C $(LIBFT_PATH)
	@$(MAKE) -C $(FTPRINTF_PATH)

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(FTPRINTF_PATH) clean
	@rm -fv $(OBJECTS)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -fv $(LIBFT_PATH)/$(LIBFT_NAME)
	@rm -fv $(FTPRINTF_PATH)/$(LIB_NAME)
	@rm -fv $(NAME_COR)

re: fclean all
