/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:52:16 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 23:35:05 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "output.h"
# include "strings.h"
# include "memory.h"
# include "lists.h"
# include "conversions.h"
# include "binary.h"

# define OPTIONS	"cspdiouxXfbkK"
# define ULL		unsigned long long

# define BLACK		"{black}"
# define RED		"{red}"
# define GREEN		"{green}"
# define YELLOW		"{yellow}"
# define BLUE		"{blue}"
# define PURPLE		"{purple}"
# define CYAN		"{cyan}"
# define GREY		"{grey}"
# define BOLD		"{bold}"
# define UNDERLINED	"{ul}"
# define NC			"{nc}"

# define FLAG		conv->flag
# define SIZE		conv->size
# define WIDTH		conv->width
# define PREC		conv->prec
# define TYPE		conv->conv_type
# define FLOATS		conv->floats
# define RET		conv->ret
# define ARG		conv->ap
# define STYLE		conv->style
# define OFFSET		conv->offset

# define RESULT		conv->floats->result
# define LEN		conv->floats->len
# define RESULT		conv->floats->result
# define IS_NEG		conv->floats->is_neg
# define P_DIFF		conv->floats->p_diff
# define SIGN		conv->floats->sign
# define EDGE		conv->floats->edge
# define B_SIZE		conv->floats->b_size
# define INDEX		conv->floats->max_index
# define F_LEN		conv->floats->f_len

typedef struct		s_flag
{
	int				zero;
	int				space;
	int				sharp;
	int				plus;
	int				less;
}					t_flag;

typedef struct		s_size
{
	int				h;
	int				hh;
	int				l;
	int				ll;
	int				j;
	int				lf;
}					t_size;

typedef union		u_ftype
{
	float			f_num;
	double			d_num;
	long double		ld_num;
	long			l_num;
	int				i_num;
	short			s_num;
	char			character;
}					t_ftype;

typedef struct		s_float
{
	int				e_len;
	int				m_len;
	int				f_len;
	int				is_neg;
	int				bias;
	int				v_exp;
	int				len;
	int				p_diff;
	int				sign;
	int				edge;
	int				b_size;
	int				max_index;
	t_ftype			f_value;
	char			*binary;
	char			*mant;
	char			*exp;
	char			*result;
	char			*min;
}					t_float;

typedef struct		s_conv
{
	va_list			ap;
	t_flag			flag;
	int				width;
	int				prec;
	t_size			size;
	int				(*f[13])(struct s_conv *conv);
	int				offset;
	size_t			ret;
	char			*style;
	char			conv_type;
	char			type[13];
	t_float			*floats;
}					t_conv;

int					ft_printf(const char *format, ...);

int					check_flags(char *fmt, t_conv *conv);
int					color_check(t_conv *conv, const char *format, int *i);

int					print_c(t_conv *conv);
void				print_sp(t_conv *conv, char *output);
void				print_di(t_conv *conv, char *output);
void				print_o(t_conv *conv, char *output);
void				print_u(t_conv *conv, char *output);
void				print_x(t_conv *conv, char *output);
void				print_float(t_conv *conv);
void				print_space_before(t_conv *conv, int max, char *output);
void				print_space_after(t_conv *conv, int max);
void				print_zeros(t_conv *conv, int digits);
void				print_extra_x(t_conv *conv, int prec, int len);
void				print_extra_o(t_conv *conv, int len,
					int *prec, int is_width);

int					output_handler(char *fmt, t_conv *conv);

int					handle_di(t_conv *conv);
int					handle_o(t_conv *conv);
int					handle_u(t_conv *conv);
int					handle_xx(t_conv *conv);
int					handle_s(t_conv *conv);
int					handle_p(t_conv *conv);
int					handle_f(t_conv *conv);
int					handle_b(t_conv *conv);
int					timestamp_to_date(t_conv *conv);
int					date_to_timestamp(t_conv *conv);

void				init_fp(t_conv *conv);
void				init_conv(t_conv *conv);
int					init_floats(t_conv *conv);
char				*init_str(int size, char c);
void				del_floats(t_conv *conv);

void				str_addition(char **result, char *add);
void				str_mult_by_two(char **str, t_conv *conv);
void				str_div_by_two(char **str, t_conv *conv);
int					format_float(t_conv *conv, char *number);
char				*set_min(t_conv *conv, int exp);
int					get_float_len(char *str);

#endif
