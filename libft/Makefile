# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 17:52:27 by bwan-nan          #+#    #+#              #
#    Updated: 2019/07/03 14:25:42 by pimichau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
DBNAME = libftdb.a

CC = Clang
CFLAGS = -Wall -Werror -Wextra
IFLAGS = -I $(IPATH)
COMPILE = $(CC) -c
DEBUG = $(CC) -g -c
MKDIR = mkdir -p
CLEANUP = /bin/rm -rf

# Regular Colors
CYAN =\033[0;36m
BLUE=\033[0;34m
GREEN=\033[32m
RED=\033[0;31m
WHITE=\033[0;37m
PURPLE=\033[0;35m
YELLOW=\033[0;33m

NC=\033[0m

vpath %.c src/Binary
vpath %.c src/Conversions
vpath %.c src/Lists
vpath %.c src/Memory
vpath %.c src/Other
vpath %.c src/Output
vpath %.c src/Strings
vpath %.c src/ft_printf
vpath %.h inc/

EXEC = a.out
SRCM = main.c

# ---------------------------------- ft_printf -----------------------------------#
SRC += ft_printf.c
SRC += init_struct.c
SRC += parsing.c
SRC += output_handler.c
SRC += diouxx_conv.c
SRC += print_diouxx.c
SRC += print_csp.c
SRC += print_flags.c
SRC += float_conv.c
SRC += binary_conv.c
SRC += colors.c
SRC += float_operations.c
SRC += init_floats.c
SRC += date_conv.c
SRC += print_float.c

# ------------------------------------- Memory -----------------------------------#
SRC += ft_memalloc.c
SRC += ft_memccpy.c
SRC += ft_memchr.c
SRC += ft_memcmp.c
SRC += ft_memcpy.c
SRC += ft_memdel.c
SRC += ft_memmove.c
SRC += ft_memset.c
SRC += ft_bzero.c
SRC += ft_realloc.c

# ------------------------------------- Strings -----------------------------------#
SRC += ft_isalnum.c
SRC += ft_isalpha.c
SRC += ft_isascii.c
SRC += ft_isdigit.c
SRC += ft_isnumeric.c
SRC += ft_isinteger.c
SRC += ft_islower.c
SRC += ft_isprint.c
SRC += ft_isupper.c
SRC += ft_iswhitespace.c
SRC += ft_strcat.c
SRC += ft_strchr.c
SRC += ft_strclr.c
SRC += ft_strcmp.c
SRC += ft_strcpy.c
SRC += ft_strdel.c
SRC += ft_strdup.c
SRC += ft_strequ.c
SRC += ft_striter.c
SRC += ft_striteri.c
SRC += ft_strjoin.c
SRC += ft_strlcat.c
SRC += ft_strlen.c
SRC += ft_strmap.c
SRC += ft_strmapi.c
SRC += ft_strncat.c
SRC += ft_strncmp.c
SRC += ft_strncpy.c
SRC += ft_strnequ.c
SRC += ft_strnew.c
SRC += ft_strnstr.c
SRC += ft_strrchr.c
SRC += ft_strsplit.c
SRC += ft_split_whitespaces.c
SRC += ft_strstr.c
SRC += ft_strsub.c
SRC += ft_strtrim.c
SRC += ft_tolower.c
SRC += ft_toupper.c
SRC += ft_strtoupper.c
SRC += ft_strtolower.c
SRC += ft_str_notchr.c
SRC += ft_strchr_index.c
SRC += ft_str_notchr_index.c
SRC += ft_strr_notchr_index.c
SRC += count_occurence.c
SRC += variadic_strjoin.c
SRC += ft_strstr_delim.c
SRC += str_isascii.c

# ------------------------------------- Conversions -----------------------------------#
SRC += ft_atoi.c
SRC += ft_atoull.c
SRC += ft_binatoi.c
SRC += ft_itoa.c
SRC += ft_itoa_base.c
SRC += ft_llitoa.c
SRC += ft_llitoa_base.c
SRC += ft_ullitoa.c
SRC += ft_ullitoa_base.c
SRC += get_bits.c

# --------------------------------------- Lists ---------------------------------------#
SRC += ft_lstnew.c
SRC += ft_lstprepend.c
SRC += ft_lstappend.c
SRC += ft_lstclr.c
SRC += ft_lstdel.c
SRC += ft_lstdelone.c
SRC += ft_lstiter.c
SRC += ft_islist_sorted.c
SRC += ft_lstswap.c
SRC += ft_lstpush.c
SRC += ft_lstrotate.c
SRC += ft_lstrevrotate.c
SRC += ft_lstcount.c
SRC += ft_lstcpy.c
SRC += ft_lstncpy.c
SRC += ft_lstpop.c

# --------------------------------------- Output --------------------------------------#
SRC += ft_putchar.c
SRC += ft_putchar_fd.c
SRC += ft_putendl.c
SRC += ft_putendl_fd.c
SRC += ft_putnbr.c
SRC += ft_putnbr_fd.c
SRC += ft_putstr.c
SRC += ft_putstr_fd.c
SRC += ft_putnbrendl.c
SRC += ft_show_tab.c
SRC += get_next_line.c

# ---------------------------------- Sorting Algorithms----------------------------------#
SRC += ft_lst_mergesort.c
SRC += ft_lst_bubblesort.c
SRC += sort_int_tab.c
SRC += ft_lstrev.c

# ----------------------------------------- Maths-----------------------------------------#
SRC += ft_power.c
SRC += ft_recursive_power.c
SRC += ft_max.c

INC = libft.h
IPATH = inc/
OPATH = obj/

OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRC))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(SRC))

DSYM += $(NAME).dSYM
DSYM += $(DBNAME).dSYM

all: $(OPATH) $(NAME)

debug : $(OPATH) $(DBNAME)

$(DBNAME): $(OBJD)
	ar -rusc $@ $^
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(NAME): $(OBJS)
	ar -rusc $@ $^
	ranlib $@
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJD): $(OPATH)db%.o : %.c $(INC)
	$(DEBUG) $(CFLAGS) $(IFLAGS) $< -o $@
	printf "$(BLUE)Compiling $< for debug\n$(NC)"

$(OBJS): $(OPATH)%.o : %.c $(INC)
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@
	printf "$(YELLOW)Compiling $<\n$(NC)"

$(OPATH):
	$(MKDIR) $@

cleandb:
	$(CLEANUP) $(DBNAME)
	printf "$(RED)$(DBNAME) deleted\n$(NC)"

clean:
	$(CLEANUP) $(OBJS)
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(EXEC)
	$(CLEANUP) $(DSYM)
	printf "$(RED)All objects removed from Libft\n$(NC)"

fclean: clean cleandb
	$(CLEANUP) $(NAME)
	printf "$(RED)$(NAME) deleted\n$(NC)"

re: fclean all

.PHONY: all clean fclean re
.SILENT:
