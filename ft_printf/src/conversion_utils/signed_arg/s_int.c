/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_int.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:29:44 by kamitsui          #+#    #+#             */
/*   Updated: 2023/03/20 17:30:29 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

long long	s_int(t_sm *machine)
{
	int	num;

	num = va_arg(*(machine->ap), int);
	return ((long long)num);
}
