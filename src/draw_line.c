/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:35:07 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/30 17:56:01 by kamitsui         ###   ########.fr       */
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

// propo is: Proportion of moving points to line span
int	transition_color(int start, int end, int move_point, t_Color *color)
{
	int	span;
	int	propo;
	int	tr_r;
	int	tr_g;
	int	tr_b;

	span = end - start;
	propo = (move_point - start) * 255 / span;
	tr_r = color->start_r + ((color->end_r - color->start_r) * propo) / 255;
	tr_g = color->start_g + ((color->end_g - color->start_g) * propo) / 255;
	tr_b = color->start_b + ((color->end_b - color->start_b) * propo) / 255;
	return ((tr_r << 16) | (tr_g << 8) | tr_b);
}

//int	transition_color(t_line *line, t_WireFR *screen, t_Color *color)
//{
//	int	start;
//	int	end;
//	int	move_point;
//
//	return (get_current_color)
//	if (line->dx > 0)
//		start = screen->x1;
//	else
//		start = screen->y0;
//		current_color = transition_color(start_y, screen->y1, screen->y0, &color);
//		current_color = get_current_color(start, end, move_point, &color);
//}

void	init_color(t_Color *color, int start_color, int end_color)
{
	color->start_r = (start_color >> 16) & 0xFF;
	color->start_g = (start_color >> 8) & 0xFF;
	color->start_b = start_color & 0xFF;
	color->end_r = (end_color >> 16) & 0xFF;
	color->end_g = (end_color >> 8) & 0xFF;
	color->end_b = end_color & 0xFF;
}

void	init_line(t_line *line, t_WireFR *screen)
{
	line->px = screen->x0;
	line->py = screen->y0;
	line->dx = ft_abs(screen->x1 - screen->x0);
	line->dy = ft_abs(screen->y1 - screen->y0);
	line->sx = less_than(screen->x0, screen->x1);
	line->sy = less_than(screen->y0, screen->y1);
	line->err = line->dx - line->dy;
}

// Bresenham's line algorithm
void	draw_line(t_data *data, t_WireFR *screen)
{
	t_line	line;
	t_Color	color;
	int		current_color;

	screen->color0 = C_WHITE;
	screen->color1 = C_RED;
	init_line(&line, screen);
	init_color(&color, screen->color0, screen->color1);
	while (1)
	{
		//transition_color(line,);
		if (line.dx > 0)
			current_color = transition_color(screen->x0, screen->x1, line.px, &color);
		else
			current_color = transition_color(screen->y0, screen->y1, line.py, &color);
		my_mlx_pixel_put(data, line.px, line.py, current_color);
		if (line.px == screen->x1 && line.py == screen->y1)
			break ;
		line.err2 = 2 * line.err;
		if (line.err2 > -line.dy)
		{
			line.err -= line.dy;
			line.px += line.sx;
		}
		if (line.err2 < line.dx)
		{
			line.err += line.dx;
			line.py += line.sy;
		}
	}
}
