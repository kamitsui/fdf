/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_va_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:13:29 by kamitsui          #+#    #+#             */
/*   Updated: 2023/03/25 17:09:40 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "process.h"
#include "conversion.h"
#include "va_arg.h"

long long	s_va_arg(t_sm *machine)
{
	long long			num;
	int					i;
	int					bit_offset;
	static t_f_s_va_arg	f_s_va_arg[5] = {s_hh, s_ll, s_h, s_l, s_int};

	bit_offset = NB_FLAG + NB_FIELD + 1;
	i = 0;
	while (i < NB_PREFIX)
	{
		if ((machine->flag & (1 << i << bit_offset)) != FALSE)
		{
			num = f_s_va_arg[i](machine);
			return (num);
		}
		i++;
	}
	num = (long long)f_s_va_arg[i](machine);
	return (num);
}
//debug code
//#include <stdio.h>//for debug
//#include "libft.h"//for debug
//	printf("%d:flag\n", machine->flag);//for debug
