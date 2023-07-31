/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:35:07 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/31 16:32:08 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

// propo is: Proportion of moving points to line span
static int	transition_color(int start, int end, int move_point, t_clr *color)
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

static int	get_current_color(t_line *line, t_wire *screen, t_clr *color)
{
	int	start;
	int	end;
	int	move_point;

	if (line->dx > 0)
	{
		start = screen->x0;
		end = screen->x1;
		move_point = line->px;
	}
	else
	{
		start = screen->y0;
		end = screen->y1;
		move_point = line->py;
	}
	return (transition_color(start, end, move_point, color));
}

static void	draw_loop(t_line *line, t_wire *screen, t_clr *color, t_data *data)
{
	while (1)
	{
		line->pc = get_current_color(line, screen, color);
		my_mlx_pixel_put(data, line->px, line->py, line->pc);
		if (line->px == screen->x1 && line->py == screen->y1)
			break ;
		line->err2 = 2 * line->err;
		if (line->err2 > -line->dy)
		{
			line->err -= line->dy;
			line->px += line->sx;
		}
		if (line->err2 < line->dx)
		{
			line->err += line->dx;
			line->py += line->sy;
		}
	}
}

// Bresenham's line algorithm
void	draw_line(t_data *data, t_wire *screen)
{
	t_line	line;
	t_clr	color;

	init_line(&line, screen);
	init_color(&color, screen->color0, screen->color1);
	draw_loop(&line, screen, &color, data);
}
//	screen->color0 = C_WHITE;
//	screen->color1 = C_RED;
//	while (1)
//	{
//		if (line.dx > 0)
//			line.pc = transition_color(screen->x0, screen->x1, line.px, &color);
//		else
//			line.pc = transition_color(screen->y0, screen->y1, line.py, &color);
//		my_mlx_pixel_put(data, line.px, line.py, line.pc);
//		if (line.px == screen->x1 && line.py == screen->y1)
//			break ;
//		line.err2 = 2 * line.err;
//		if (line.err2 > -line.dy)
//		{
//			line.err -= line.dy;
//			line.px += line.sx;
//		}
//		if (line.err2 < line.dx)
//		{
//			line.err += line.dx;
//			line.py += line.sy;
//		}
//	}
