/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:47:03 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/27 22:56:20 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// Error code
//enum e_state
//{
//	ERR_ARG,
//	ERR_MLX,
//	ERR_WIN,
//};

// Error message
# define MSG_MLX	"Error: Failed to initialize MiniLibX\n"
# define MSG_WIN	"Error: Failed to create a window\n"
# define MSG_MAP	"Error: Unmatched number of columns elements in Map file\n"

// Error number
# define ERR_MLX	0
# define ERR_WIN	1
# define ERR_MAP	2
# define ERR_NUM	3

/*
 * Window configuration
 */
# define WIN_WIDTH		1000  // Width of the window
# define WIN_HEIGHT		800 // Height of the window
# define IMG_WIDTH		800  // Width of the window
# define IMG_HEIGHT		600 // Height of the window
# define TILE_SIZE		15   // Size of each tile
# define COLOR			0xFFFFFF // Color value for points and lines (white)
# define OFFSET_X		300
# define OFFSET_Y		150
# define KEY_ESC		0xff1b
# define PROGRAM_NAME	"fdf"
# define DELIMITERS		" ,"
//# define WINDOW_WIDTH	1200
//# define WINDOW_HEIGHT	900
//# define WINDOW_HEIGHT	108000

// Structure : Bresenham's line algorithm
typedef struct s_line {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
}	t_line;

// FDF data structure

typedef struct s_wire {
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_WireFR;

typedef struct s_Map
{
	int	rows;
	int	cols;
}	t_Map;

typedef struct s_Point3D
{
	int	x;
	int	y;
	int	z;
}	t_Point3D;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_data;

typedef struct s_fdf {
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		*data;
	t_Point3D	**points;
	t_Map		*map;
}	t_fdf;
//	*mlx_ptr;	// MiniLibX graphics system pointer
//	*win_ptr;	// Window pointer
//	*data;		// Image pointer
//	**points;	// 2D array to store the points
//	*map;		// Map size

void	draw_wireframe_model(t_data *data, t_Point3D **points,
			int rows, int cols);
void	draw_line(t_data *data, t_WireFR screen);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	read_map(char *file, t_fdf *fdf);
void	set_points(char *file, t_Point3D **points, int rows, int cols);
void	error_fdf(int error_code);
void	ft_errno_exit(char *cause);
void	ft_perror_exit(char *message);

#endif
