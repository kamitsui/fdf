/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:05:41 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/19 15:12:13 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

static void	error_message(int error_code)
{
	static char	*msg[ERR_NUM] = {MSG_ARG, MSG_MLX};
	ft_fprintf(stderr, msg[error_code]);
}

void	error_fdf(int error_code)
{
	error_message(error_code);
	exit(error_code);
}

void	ft_errno_exit(char *cause)
{
	int		error_number;
	char	*error_message;

	error_number = errno;
	error_message = strerror(error_number);
	ft_fprintf(stderr, "bash: %s: %s\n", cause, error_message);
	exit (1);
}

void	ft_perror_exit(char *message)
{
	perror(message);
	exit (1);
}
