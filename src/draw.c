/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:07:22 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/27 23:00:55 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>// for abs()  delete!!!

static void	set_screen_point(t_Point3D points, int *screen_x, int *screen_y)
{
	*screen_x = (points.x - points.y) * TILE_SIZE + OFFSET_X;
	*screen_y = (points.x + points.y) * TILE_SIZE + OFFSET_Y
		- points.z * TILE_SIZE;
}

static void	connect_two_points(t_data *data, t_WireFR screen,
		t_Point3D next_point)
{
	set_screen_point(next_point, &screen.x1, &screen.y1);
	draw_line(data, screen);
}

void	draw_wireframe_model(t_data *data, t_Point3D **points,
		int rows, int cols)
{
	t_WireFR	screen;
	int			i;
	int			j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			set_screen_point(points[i][j], &screen.x0, &screen.y0);
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
