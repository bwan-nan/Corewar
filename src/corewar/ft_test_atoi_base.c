/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_atoi_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:35:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/17 17:53:53 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static	void		ft_test(int n)
{
	char	*str;

	str = ft_itoa_base(n, 2);
	ft_printf("   n:%d\nitoa:%s\natoi:%d\n\n", n, str, ft_atoi_base(str, 2));
	free(str);
}

void				ft_test_atoi_base(void)
{
	ft_test(0);
	ft_test(1);
	ft_test(2);
	ft_test(3);
	ft_test(4);
	ft_test(5);
	ft_test(8);
	ft_test(9);
	ft_test(10);
	ft_test(15);
	ft_test(16);
	ft_test(32);
	ft_test(64);
	ft_test(128);
	ft_test(256);
	ft_test(512);
	ft_test(1024);
	ft_test(2048);
	ft_test(4096);
	ft_test(8192);
	ft_test(16384);
	ft_test(32768);
	ft_test(65536);
	ft_test(131072);
	ft_test(262144);
	ft_test(524288);
	ft_test(1048576);
	ft_test(1048576);
	ft_test(2097152);
	ft_test(2097152);
	ft_test(4194304);
	ft_test(8388608);
	ft_test(16777216);
	ft_test(33554432);
	ft_test(67108864);
	ft_test(134217728);
	ft_test(268435456);
	ft_test(2147483647);
	ft_test(214483647);
	ft_test(14483647);
	ft_test(2144647);
	ft_test(214647);
	ft_test(83647);
	ft_test(2647);
	ft_test(647);
	ft_test(66);
	ft_test(9);
	ft_test(-1);
	ft_test(-10);
	ft_test(-100);
	ft_test(-1000);
	ft_test(-10000);
	ft_test(-100000);
	ft_test(-10000000);
	ft_test(-1000000000);
	ft_test(-2147483648);
}
