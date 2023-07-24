/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:07:22 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/24 16:21:07 by kamitsui         ###   ########.fr       */
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

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int err2;

	while (1)
	{
		my_mlx_pixel_put(data, x0, y0, color);
		if (x0 == x1 && y0 == y1)
		break;
		err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

#include "ft_printf.h"

void draw_wireframe_model(t_data *data, Point3D **points, int rows, int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Point3D current_point = points[i][j];

			// Calculate the screen coordinates using isometric projection
			//int screen_x = (current_point.x - current_point.y) * TILE_SIZE;
			//int screen_y = (current_point.x + current_point.y) * TILE_SIZE - current_point.z * TILE_SIZE;
			int screen_x = (current_point.x - current_point.y) * TILE_SIZE + OFFSET_X;
			int screen_y = (current_point.x + current_point.y) * TILE_SIZE - current_point.z * TILE_SIZE + OFFSET_Y;

			// Draw the point
			my_mlx_pixel_put(data, screen_x, screen_y, COLOR);

			// Connect adjacent points with lines to create the wireframe
			if (j < cols - 1) {
				Point3D next_point = points[i][j + 1];
				int next_screen_x = (next_point.x - next_point.y) * TILE_SIZE + OFFSET_X;
				int next_screen_y = (next_point.x + next_point.y) * TILE_SIZE - next_point.z * TILE_SIZE + OFFSET_Y;
				draw_line(data, screen_x, screen_y, next_screen_x, next_screen_y, COLOR);
			}
			if (i < rows - 1) {
				Point3D next_point = points[i + 1][j];
				int next_screen_x = (next_point.x - next_point.y) * TILE_SIZE + OFFSET_X;
				int next_screen_y = (next_point.x + next_point.y) * TILE_SIZE - next_point.z * TILE_SIZE + OFFSET_Y;
				draw_line(data, screen_x, screen_y, next_screen_x, next_screen_y, COLOR);
			}
		}
	}
}
