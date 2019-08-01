# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:04:21 by bwan-nan          #+#    #+#              #
#    Updated: 2019/08/01 14:55:18 by bwan-nan         ###   ########.fr        #
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
SPATH = src/ASM/
IPATH = inc/
LPATH = libft/
LIPATH = libft/inc/

ASM_INCS += asm.h

ASM += asm.c
ASM += check_header.c
ASM += check_quote.c
ASM += header_status.c
ASM += update_labels.c
ASM += check_content.c
ASM += check_instruction.c
ASM += check_params.c
ASM += instruction_tools.c
ASM += custom_split.c
ASM += get_input.c
ASM += lexing.c
ASM += op.c
ASM += queue.c
ASM += reorder_list.c
ASM += create_cor_file.c
ASM += free_program.c
ASM += is_asm_file.c
ASM += print_error.c


DSYM = $(NAME).dSYM

OBJ = $(patsubst %.c, $(OPATH)%.o, $(ASM))

vpath	%.c src/ASM/
vpath	%.c src/ASM/lexing
vpath	%.c src/ASM/tools

vpath	%.h inc/
vpath	%.h libft/inc/

all : $(LIB) $(NAME)

debug : $(LIBDB) $(ASM)
	$(MAKE) -C $(LPATH) debug
	$(DEBUG) $(DFLAGS) $(CFLAGS) -o $(NAME) $^

$(NAME): $(LIB) $(OPATH) $(OBJ) $(ASM_INCS)
	$(CC) -o $@ $< $(OBJ)
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJ) : $(OPATH)%.o : %.c $(ASM_INCS)
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
