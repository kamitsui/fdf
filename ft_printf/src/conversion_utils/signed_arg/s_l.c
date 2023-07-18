/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_l.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:27:20 by kamitsui          #+#    #+#             */
/*   Updated: 2023/03/20 18:32:15 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

long long	s_l(t_sm *machine)
{
	long	num;

	num = va_arg(*(machine->ap), long);
	return ((long long)num);
}
