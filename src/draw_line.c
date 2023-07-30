/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:35:07 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/30 13:42:06 by kamitsui         ###   ########.fr       */
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

# define C_WHITE	0xffffff
# define C_GREY		0x303030
# define C_RED		0xff0000

// Bresenham's line algorithm
void	draw_line(t_data *data, t_WireFR *screen)
{
	t_line	line;

	line.dx = ft_abs(screen->x1 - screen->x0);
	line.dy = ft_abs(screen->y1 - screen->y0);
	line.sx = less_than(screen->x0, screen->x1);
	line.sy = less_than(screen->y0, screen->y1);
	line.err = line.dx - line.dy;

	int	start_color = C_WHITE;
	int	end_color = C_RED;
	int	start_x = screen->x0;
	int	start_y = screen->y0;
	int start_red = (start_color >> 16) & 0xFF;
	int start_green = (start_color >> 8) & 0xFF;
	int start_blue = start_color & 0xFF;
	
	int end_red = (end_color >> 16) & 0xFF;
	int end_green = (end_color >> 8) & 0xFF;
	int end_blue = end_color & 0xFF;
	while (1)
	{
	int proportion = (screen->x1 - screen->x0) ? (screen->x0 - start_x) * 255 / line.dx : (screen->y0 - start_y) * 255 / (line.dy);
	int current_red = start_red + ((end_red - start_red) * proportion) / 255;
	int current_green = start_green + ((end_green - start_green) * proportion) / 255;
	int current_blue = start_blue + ((end_blue - start_blue) * proportion) / 255;
	int current_color = (current_red << 16) | (current_green << 8) | current_blue;
		my_mlx_pixel_put(data, screen->x0, screen->y0, current_color);
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
