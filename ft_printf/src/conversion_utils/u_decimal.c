/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_decimal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:44:02 by kamitsui          #+#    #+#             */
/*   Updated: 2023/03/29 18:13:25 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_printf.h"
#include "process.h"
#include "conversion.h"
#include "va_arg.h"
#include "formalize.h"
#include "libft.h"

void	u_decimal(t_sm *machine)
{
	char				str[42];
	unsigned long long	num;
	int					base;

	ft_bzero(str, 42);
	base = 10;
	num = u_va_arg(machine);
	if (!((machine->flag & BIT_PREC) && (machine->prec == 0) && (num == 0)))
		itoa_buff(num, str, base, machine);
	formalize(str, machine);
}
