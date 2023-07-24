/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:47:03 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/24 15:55:15 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// Error code
//enum e_state
//{
//	ERR_ARG,
//	ERR_MLX,
//	ERR_WINDOW
//};

// Error message
# define MSG_ARG	"Error: Insufficient arguments. Bye!! :)\n"
# define MSG_MLX	"Error: Failed to initialize MiniLibX\n"
# define MSG_WINDOW	"Error: Failed to create a window\n"
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
# define WINDOW_NAME	"fdf"
//# define WINDOW_WIDTH	1200
//# define WINDOW_HEIGHT	900
//# define WINDOW_HEIGHT	108000

// FDF data structure
typedef struct
{
    int rows;
    int cols;
} Map;

typedef struct
{
    int x;
    int y;
    int z;
} Point3D;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_data;

typedef struct	s_fdf {
    void	*mlx_ptr;      // MiniLibX graphics system pointer
    void	*win_ptr;      // Window pointer
	t_data	*data;		// Image pointer
    Point3D	**points;   // 2D array to store the points
	Map		*map; // Map size
} t_fdf;

void draw_wireframe_model(t_data *data, Point3D **points, int rows, int cols);
void	read_map(char *file, t_fdf *fdf);
void	error_fdf(int error_code);
void	ft_errno_exit(char *cause);
void	ft_perror_exit(char *message);

#endif

//typedef struct s_fdf
//{
//	t_map	*map;
//	void	*mlx;
//	int		window_x;
//	int		window_y;
//	void	*window;
//	t_data	*data;
////	t_camera	*camera;
//}	t_fdf;

// Image data structure
//typedef struct s_data
//{
//	void	*img;
//	char	*addr;
//	int		bits_per_pixel;
//	int		line_length;
//	int		endian;
//	t_line	*line;
//}	t_data;

// Current line being printed
//typedef struct s_line
//{
//	t_point	start;
//	t_point	end;
//	float	transform_z;
//}	t_line;

// Single point structure
//typedef struct s_point
//{
//	float	x;
//	float	y;
//	float	z;
//	int		color;
//}	t_point;
