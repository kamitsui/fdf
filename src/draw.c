/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:07:22 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/25 23:00:02 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>// for abs()  delete!!!

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_line(t_data *data, t_wire screen)
{
	int dx = abs(screen.x1 - screen.x0);
	int dy = abs(screen.y1 - screen.y0);
	int sx = (screen.x0 < screen.x1) ? 1 : -1;
	int sy = (screen.y0 < screen.y1) ? 1 : -1;
	int err = dx - dy;
	int err2;

	while (1)
	{
		my_mlx_pixel_put(data, screen.x0, screen.y0, COLOR);
		if (screen.x0 == screen.x1 && screen.y0 == screen.y1)
		break;
		err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			screen.x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			screen.y0 += sy;
		}
	}
}

static void	set_screen_point(Point3D points, int *screen_x, int *screen_y)
{
	*screen_x = (points.x - points.y) * TILE_SIZE + OFFSET_X;
	*screen_y = (points.x + points.y) * TILE_SIZE - points.z * TILE_SIZE + OFFSET_Y;
}

static void	connect_two_points(t_data *data, t_wire screen, Point3D next_point)
{
	set_screen_point(next_point, &screen.x1, &screen.y1);
	draw_line(data, screen);
}

void	draw_wireframe_model(t_data *data, Point3D **points, int rows, int cols)
{
	t_wire	screen;
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			set_screen_point(points[i][j], &screen.x0, &screen.y0);// previsional
			my_mlx_pixel_put(data, screen.x0, screen.y0, COLOR);
			if (j < cols - 1)
				connect_two_points(data, screen, points[i][j + 1]);
			if (i < rows - 1)
				connect_two_points(data, screen, points[i + 1][j]);
			j++;
		}
		i++;
	}
}
//#include "ft_printf.h"
//	ft_printf("rows:%d cols:%d\n", rows, cols);
