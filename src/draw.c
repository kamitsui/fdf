/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:07:22 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/31 23:25:56 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include "ft_printf.h"//for debug

// Function to perform isometric projection
static void	set_screen_point(t_Point3D points,
		int *new_x, int *new_y, int *new_color)
{
	int	old_x;
	int	old_y;
	int	old_z;

	old_x = points.x * TILE_SIZE;
	old_y = points.y * TILE_SIZE;
	old_z = points.z * TILE_SIZE;
	*new_x = (int)(cos(ANGLE_Y) * (old_x) - cos(ANGLE_Y) * (old_y)) + OFFSET_X;
	*new_y = (int)(sin(ANGLE_X) * (old_x) + sin(ANGLE_X) * (old_y)) + OFFSET_Y
		- old_z;
	*new_color = points.color;
}

static void	connect_two_points(t_data *data, t_wire screen,
		t_Point3D next_point)
{
	set_screen_point(next_point, &screen.x1, &screen.y1, &screen.color1);
	draw_line(data, &screen);
	ft_printf("after draw_line()\n");
}

void	draw_wireframe_model(t_data *data, t_Point3D **points,
		int rows, int cols)
{
	t_wire	screen;
	int		i;
	int		j;

	ft_printf("rows:%d cols:%d\t\tin draw_wireframe_model()\n", rows, cols);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			set_screen_point(points[i][j], &screen.x0, &screen.y0,
				&screen.color0);
//			if ((screen.x0 <= IMG_WIDTH && screen.x0 >= 0) ||
//						(screen.y0 <= IMG_HEIGHT && screen.y0 >= 0))
			if (screen.x0 >= IMG_WIDTH || screen.x0 <= 0 ||
						screen.y0 >= IMG_HEIGHT || screen.y0 <= 0)
				break ;
			my_mlx_pixel_put(data, screen.x0, screen.y0, screen.color0);
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
//	ft_printf("rows:%d cols:%d\tin draw_wireframe_model()\n", rows, cols);
