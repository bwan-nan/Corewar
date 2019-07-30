# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:04:21 by bwan-nan          #+#    #+#              #
#    Updated: 2019/07/25 17:12:13 by bwan-nan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm
LIB = $(LPATH)libft.a
LIBDB = $(LPATH)libftdb.a

# Reset
NC=\033[0m

# Regular Colors
BLACK=\033[0;30m
RED=\033[0;31m
GREEN =\033[32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m

CC = Clang
COMPILE = $(CC) -c
DEBUG = $(CC) -g

MKDIR = mkdir -p
CLEANUP = rm -rf

WFLAGS += -Wall
WFLAGS += -Werror
WFLAGS += -Wextra
DFLAGS = -fsanitize=address
IFLAGS = -I $(IPATH) -I $(LIPATH)
CFLAGS = $(WFLAGS) $(IFLAGS)

OPATH = obj/
SPATH = src/
IPATH = inc/
LPATH = libft/
LIPATH = libft/inc/

INCS += asm.h

SRC += asm.c
SRC += check_header.c
SRC += check_quote.c
SRC += header_status.c
SRC += update_labels.c
SRC += check_content.c
SRC += check_instruction.c
SRC += check_params.c
SRC += instruction_tools.c
SRC += custom_split.c
SRC += get_input.c
SRC += lexing.c
SRC += op.c
SRC += queue.c
SRC += reorder_list.c
SRC += create_cor_file.c
SRC += free_program.c
SRC += is_asm_file.c


DSYM = $(NAME).dSYM

OBJ = $(patsubst %.c, $(OPATH)%.o, $(SRC))

vpath	%.c src/
vpath	%.c src/lexing
vpath	%.c src/tools

vpath	%.h inc/
vpath	%.h libft/inc/

all : $(LIB) $(NAME)

debug : $(LIBDB) $(SRC)
	$(MAKE) -C $(LPATH) debug
	$(DEBUG) $(DFLAGS) $(CFLAGS) -o $(NAME) $^

$(NAME): $(LIB) $(OPATH) $(OBJ) $(INCS)
	$(CC) -o $@ $< $(OBJ)
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJ) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $< -o $@
	printf "$(CYAN)Compiling $<\n$(NC)"

$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

$(LIBDB) :
	$(MAKE) -C $(LPATH) debug

$(OPATH):
	$(MKDIR) $@

clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OBJ)
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(DSYM)
	printf "$(RED)All objects removed from asm\n$(NC)"

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(NAME)
	printf "$(RED)$(NAME) deleted\n$(NC)"

re: fclean all

.PHONY: all clean fclean debug
FORCE:
.SILENT:
