/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:47:03 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/13 20:34:11 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// Error code
enum e_state
{
	ERR_ARG,
	ERR_MLX,
	ERR_WINDOW
};

// Error message
# define MSG_ARG	"Error: Insufficient arguments. Bye!! :)\n"
# define MSG_MLX	"Error: Failed to initialize MiniLibX\n"
# define MSG_WINDOW	"Error: Failed to create a window\n"
# define MSG_NUM	3

/*
 * Window configuration
 */
# define WINDOW_NAME	"fdf"
# define WINDOW_WIDTH	1200
# define WINDOW_HEIGHT	900
//# define WINDOW_HEIGHT	108000

// FDF data structure
typedef struct s_fdf
{
	t_map	*map;
	void	*mlx;
	int		window_x;
	int		window_y;
	void	*window;
	t_data	*data;
//	t_camera	*camera;
}	t_fdf;

// Image data structure
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_line	*line;
}	t_data;

// Current line being printed
typedef struct s_line
{
	t_point	start;
	t_point	end;
	float	transform_z;
}	t_line;

// Single point structure
typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

#endif
