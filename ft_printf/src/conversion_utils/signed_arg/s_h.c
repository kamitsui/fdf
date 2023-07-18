/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_h.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:25:47 by kamitsui          #+#    #+#             */
/*   Updated: 2023/03/25 21:00:02 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

long long	s_h(t_sm *machine)
{
	short	num;

	num = (short)va_arg(*(machine->ap), int);
	return ((long long)num);
}
//note
//num = (short)va_arg(*(machine->ap), short);
//complie error:	this va_arg has undefined behavior
//					because type short will be promoted to int.
