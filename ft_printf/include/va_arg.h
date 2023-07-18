/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_arg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:18:08 by kamitsui          #+#    #+#             */
/*   Updated: 2023/03/25 16:23:08 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VA_ARG_H
# define VA_ARG_H

typedef unsigned long long	(*t_f_u_va_arg)(t_sm *);
unsigned long long	u_hh(t_sm *machine);
unsigned long long	u_ll(t_sm *machine);
unsigned long long	u_h(t_sm *machine);
unsigned long long	u_l(t_sm *machine);
unsigned long long	u_int(t_sm *machine);
unsigned long long	u_va_arg(t_sm *machine);

typedef long long			(*t_f_s_va_arg)(t_sm *);
long long			s_hh(t_sm *machine);
long long			s_ll(t_sm *machine);
long long			s_h(t_sm *machine);
long long			s_l(t_sm *machine);
long long			s_int(t_sm *machine);
long long			s_va_arg(t_sm *machine);

#endif
