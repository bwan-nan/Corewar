# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:04:21 by bwan-nan          #+#    #+#              #
#    Updated: 2019/08/01 16:41:00 by bwan-nan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
COR = corewar
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

INC_ASM += asm.h
INC_COR += corewar.h

INCS += $(INC_ASM) 
INCS += $(INC_COR)

ASM_SRC += asm.c
ASM_SRC += check_header.c
ASM_SRC += check_quote.c
ASM_SRC += header_status.c
ASM_SRC += update_labels.c
ASM_SRC += check_content.c
ASM_SRC += check_instruction.c
ASM_SRC += check_params.c
ASM_SRC += instruction_tools.c
ASM_SRC += custom_split.c
ASM_SRC += get_input.c
ASM_SRC += lexing.c
ASM_SRC += op_asm.c
ASM_SRC += queue.c
ASM_SRC += reorder_list.c
ASM_SRC += create_cor_file.c
ASM_SRC += free_program.c
ASM_SRC += is_asm_file.c
ASM_SRC += print_error.c

COR_SRC += op_cor.c
COR_SRC += ft_str_is_numeric.c
COR_SRC += ft_init_conf.c
COR_SRC += ft_end.c	
COR_SRC += ft_check_args.c			
COR_SRC += ft_check_players.c		
COR_SRC += ft_champion_parser.c		
COR_SRC += ft_init_arena.c			
COR_SRC += ft_launch_arena.c			
COR_SRC += ft_check_args_size.c		
COR_SRC += ft_check_cycle_to_die.c	
COR_SRC += ft_print_visu.c			
COR_SRC += ft_print_grid.c			
COR_SRC += ft_print_xml.c			
COR_SRC += ft_clean.c				
COR_SRC += c_tools.c					
COR_SRC += c_live_zjmp_aff.c			
COR_SRC += c_ld_st_ldi_sti.c			
COR_SRC += c_add_sub_and_or_xor.c	
COR_SRC += c_fork_lfork.c			
COR_SRC += c_lld_lldi.c				
COR_SRC += main.c

SRCS += $(COR_SRC)
SRCS += $(ASM_SRC)

DSYM = $(ASM).dSYM

#OBJ = $(patsubst %.c, $(OPATH)%.o, $(SRCS))
OBJ_ASM = $(patsubst %.c, $(OPATH)%.o, $(ASM_SRC))
OBJ_COR = $(patsubst %.c, $(OPATH)%.o, $(COR_SRC))

vpath	%.c src/ASM/
vpath	%.c src/ASM/lexing/
vpath	%.c src/ASM/tools/

vpath	%.c src/corewar/

vpath	%.h inc/
vpath	%.h libft/inc/

all : $(LIB) $(ASM) $(COR) 

debug : $(LIBDB) $(ASM_SRC)
	$(MAKE) -C $(LPATH) debug
	$(DEBUG) $(DFLAGS) $(CFLAGS) -o $(ASM) $^

$(ASM): $(LIB) $(OPATH) $(OBJ_ASM) $(INC_ASM)
	$(CC) -o $@ $< $(OBJ_ASM)
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(COR): $(LIB) $(OPATH) $(OBJ_COR) $(INC_COR)
	$(CC) -o $@ $< $(OBJ_COR)
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJ_ASM): $(OPATH)%.o : %.c $(INC_ASM)
	$(COMPILE) $(CFLAGS) $< -o $@
	printf "$(CYAN)Compiling $<\n$(NC)"

$(OBJ_COR): $(OPATH)%.o : %.c $(INC_COR)
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
	printf "$(RED)All objects removed from corewar\n$(NC)"

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(ASM)
	$(CLEANUP) $(COR)
	printf "$(RED)$(ASM) deleted\n$(NC)"
	printf "$(RED)$(COR) deleted\n$(NC)"

re: fclean all

.PHONY: all clean fclean debug
FORCE:
.SILENT:
