/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:35:07 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/28 17:37:00 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static int	less_than(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

// Bresenham's line algorithm
void	draw_line(t_data *data, t_WireFR *screen)
{
	t_line	line;

	line.dx = ft_abs(screen->x1 - screen->x0);
	line.dy = ft_abs(screen->y1 - screen->y0);
	line.sx = less_than(screen->x0, screen->x1);
	line.sy = less_than(screen->y0, screen->y1);
	line.err = line.dx - line.dy;
	while (1)
	{
		my_mlx_pixel_put(data, screen->x0, screen->y0, COLOR);
		if (screen->x0 == screen->x1 && screen->y0 == screen->y1)
			break ;
		line.err2 = 2 * line.err;
		if (line.err2 > -line.dy)
		{
			line.err -= line.dy;
			screen->x0 += line.sx;
		}
		if (line.err2 < line.dx)
		{
			line.err += line.dx;
			screen->y0 += line.sy;
		}
	}
}
