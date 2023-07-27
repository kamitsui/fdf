/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:09:35 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/27 22:57:11 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ft_printf.h"
#include "fdf.h"

static int	my_key_function(int keycode, t_fdf *fdf)
{
	int		i;

	if (keycode == KEY_ESC)
	{
		i = 0;
		while (i < fdf->map->rows)
		{
			free(fdf->points[i]);
			i++;
		}
		free(fdf->points);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		mlx_destroy_image(fdf->mlx_ptr, fdf->data->img);
	}
	exit(0);
}

static void	error_arg(char *program_name)
{
	ft_printf("Usage : %s <filename> [ case_size z_size ]\n", program_name);
	exit (1);
}

int	main(int ac, char *av[])
{
	t_fdf	fdf;
	t_data	data;
	t_Map	map;

	fdf.data = &data;
	fdf.map = &map;
	if (ac != 2)
		error_arg(av[0]);
	read_map(av[1], &fdf);
	fdf.mlx_ptr = mlx_init();
	if (fdf.mlx_ptr == NULL)
		error_fdf(ERR_MLX);
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fdf");
	if (fdf.win_ptr == NULL)
		error_fdf(ERR_WIN);
	data.img = mlx_new_image(fdf.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.size_line, &data.endian);
	draw_wireframe_model(&data, fdf.points, fdf.map->rows, fdf.map->cols);
	mlx_clear_window(fdf.mlx_ptr, fdf.win_ptr);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, data.img, 100, 100);
	mlx_key_hook(fdf.win_ptr, &my_key_function, &fdf);
	mlx_loop(fdf.mlx_ptr);
}
// FDF data structure
//typedef struct
//{
//    int rows;
//    int cols;
//} Map;
//
//typedef struct
//{
//    int x;
//    int y;
//    int z;
//} Point3D;
//
//typedef struct	s_data {
//	void	*img;
//	char	*addr;
//	int		bits_per_pixel;
//	int		size_line;
//	int		endian;
//}				t_data;
//
//typedef struct	s_fdf {
//    void *mlx_ptr;      // MiniLibX graphics system pointer
//    void *win_ptr;      // Window pointer
//	t_data	*data;		// Image pointer
//    Point3D **points;   // 2D array to store the points
//	Map map;
//} t_fdf;
//	ft_printf("Bits per pixel: %d\n", data.bits_per_pixel);
//	ft_printf("Size of each line: %d bytes\n", data.size_line);
//	ft_printf("Endianness: %d\n", data.endian);
