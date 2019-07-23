/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:48:51 by fdagbert          #+#    #+#             */
/*   Updated: 2019/04/11 15:52:59 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define D_BUFF_SIZE 1024
# define D_PNULL "0x0"
# define D_SNULL "(null)"
# define D_WSNULL L"(null)"
# define D_FILE_ERR "Error: file could not be read"
# define D_THOUSAND_SEP ','
# define D_ENABLE_SEP_ACCU 0
# define D_ENABLE_L_LL 0
# define D_EPOCH 1970
# define D_UTC 1
# define D_ENABLE_DST 1
# define D_HEMISP_SIDE 1
# define D_TIME_LANG 1
# define D_CRYPT_KEY "E2r10P19"

# include "libft.h"
# include <stdarg.h>
# include <wchar.h>

typedef struct	s_config
{
	const char	*format;
	int			ret;
	int			fd;
	va_list		ap;
	char		buff[D_BUFF_SIZE + 1];
	int			options[10];
	int			width;
	int			accuracy;
	int			size;
	char		type;
	int			base;
	int			lenraw;
	int			lenfinal;
	int			lenstart;
	int			neg;
	int			sep;
	int			fzero;
	int			fsharp;
}				t_config;

typedef struct	s_types
{
	char		*key;
	void		(*ft_start_conv)(t_config *conf);
}				t_types;

typedef struct	s_effects
{
	char		*keys;
	char		*code;
	int			len;
}				t_effects;

typedef struct	s_time
{
	int			total_day;
	int			hour;
	int			minute;
	int			second;
	int			year;
	int			week;
	int			month;
	int			day;
	int			leap;
	int			summer;
}				t_time;

typedef union	u_conv
{
	intmax_t	j;
	uintmax_t	ju;
}				t_conv;

int				ft_printf(const char *restrict format, ...);
int				ft_check_flags(t_config *conf, const char *str);
int				ft_check_conf(t_config *conf);
int				ft_set_wild(t_config *conf, const char *str);
void			ft_addbuff(t_config *conf, char c);
void			ft_imtoa_base(t_config *conf, intmax_t n, int count);
void			ft_umtoa_base(t_config *conf, uintmax_t n, int count);
void			ft_conv_int(t_config *conf);
void			ft_fill_int(t_config *conf, t_conv *number);
void			ft_conv_new(t_config *conf, unsigned char c);
void			ft_conv_char(t_config *conf);
void			ft_conv_utf8(t_config *conf, t_conv *letter, char *byte);
void			ft_conv_string(t_config *conf);
void			ft_conv_wstr(t_config *conf);
void			ft_conv_address(t_config *conf);
void			ft_conv_pct(t_config *conf);
void			ft_conv_ctrl(t_config *conf);
void			ft_conv_date(t_config *conf);
void			ft_format_date(t_config *conf, t_time *t);
void			ft_conv_fd(t_config *conf);
void			ft_conv_file(t_config *conf);
void			ft_conv_crypt(t_config *conf);
int				ft_text_effects(t_config *conf, const char *str);

#endif
