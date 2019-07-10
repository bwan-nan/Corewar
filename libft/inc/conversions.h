/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 22:21:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/03 14:39:12 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSIONS_H
# define CONVERSIONS_H

int					ft_atoi(const char *nptr);
unsigned long long	ft_atoull(const char *nptr);
int					ft_binatoi(char *str);
char				*ft_itoa(int n);
char				*ft_itoa_base(int value, int base);
char				*ft_llitoa(long long nb);
char				*ft_llitoa_base(long long nb, int base);
char				*ft_ullitoa(unsigned long long nb);
char				*ft_ullitoa_base(unsigned long long nb, int base);

#endif
