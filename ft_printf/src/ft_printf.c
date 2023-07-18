/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:49:27 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/04 18:54:38 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>

static void	initialize_machine(t_sm *machine, va_list *ap)
{
	machine->state = LETTER;
	machine->ap = ap;
	ft_bzero((void *)&machine->buffer, (size_t)4096);
	machine->out = ft_strnew(1);
	if (machine->out == NULL)
	{
		machine->state = ERROR;
		return ;
	}
	ft_bzero((void *)machine->out, 1);
	machine->out_size = 0;
	machine->len = 0;
	machine->flag = 0x0;
	machine->width = 0;
	machine->prec = 0;
}

int	ft_printf(const char *input, ...)
{
	t_sm	machine;
	va_list	ap;

	va_start(ap, input);
	initialize_machine(&machine, &ap);
	process(input, &machine);
	if (machine.state != ERROR)
	{
		machine.out = join_to_out(machine.out, machine.buffer, machine.len);
		if (machine.out == NULL)
			return (-1);
		machine.out_size = write(1, machine.out, machine.out_size);
	}
	free(machine.out);
	va_end(ap);
	if (machine.state == ERROR)
		return (-1);
	return (machine.out_size);
}

int	ft_fprintf(FILE *stream, const char *input, ...)
{
	t_sm	machine;
	va_list	ap;
	int		fd;

	fd = fileno(stream);
	if (fd == -1)
		return (-1);
	va_start(ap, input);
	initialize_machine(&machine, &ap);
	process(input, &machine);
	if (machine.state != ERROR)
	{
		machine.out = join_to_out(machine.out, machine.buffer, machine.len);
		if (machine.out == NULL)
			return (-1);
		machine.out_size = write(fd, machine.out, machine.out_size);
	}
	free(machine.out);
	va_end(ap);
	if (machine.state == ERROR)
		return (-1);
	return (machine.out_size);
}
//void code
//		machine.out = ft_strjoin_free(machine.out, machine.buffer);
//degug code in initialize_machine
//#include <stdio.h>// for debug
//	printf("-------- initialize -------\n");// for debug
//	printf("ap (%p) || state (%d) || ",
//			machine->ap, machine->state);// for debug
//	printf("len (%d) || buffer (%s) || buff_size (%lu) || ",
//			machine->len, machine->buffer, sizeof(machine->buffer));// for debug
//	char *flag_bin = ft_itoa_binary(machine->flag);// for debug
//	printf("flag (%d) (b0%s) || ", machine->flag, flag_bin);// for debug
//	free(flag_bin);// for debug
//	printf("out (%s) || out_size (%d) || out_size (%lu)\n",
//			machine->out, machine->out_size, sizeof(machine->out));// for debug
//	debug code in ft_printf
//	printf("------- process finished ------\n");// for debug
//	printf("buffer (%s) || out (%s)\n", machine.buffer, machine.out);// for debug
//	printf("------- strjoin_free finished ------\n");// for debug
//	printf("buffer (%s) || out (%s)\n", machine.buffer, machine.out);// for debug
//	printf("+++++++ write of ft_printf +++++++\n");// for debug
//	printf("\n------- after free ------\n");// for debug
//	printf("buffer (%s) || out (%s)\n", machine.buffer, machine.out);
