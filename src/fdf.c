/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:09:35 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/24 16:30:59 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ft_printf.h"
#include "fdf.h"


int	my_key_function(int keycode, t_fdf *fdf)
{
	void *mlx_ptr = fdf->mlx_ptr;
	void *win_ptr = fdf->win_ptr;
	void *img = fdf->data->img;
	Point3D **points = fdf->points;
	int rows = fdf->map->rows;

	if (keycode == KEY_ESC)
	{
		for (int i = 0; i < rows; i++) {
			free(points[i]);
		}
		free(points);
		mlx_destroy_window(mlx_ptr, win_ptr);
		mlx_destroy_image(mlx_ptr, img);
	}
	exit(0);
}

int main(int ac, char *av[])
{
	t_fdf	fdf;
	t_data	data;
	Map		map;
	fdf.data = &data;
	fdf.map = &map;

	if (ac != 2)
	{
		printf("argument 2\n");
		return -1;
	}

	read_map(av[1], &fdf);// segmentation fault
	fdf.mlx_ptr = mlx_init();
	if (fdf.mlx_ptr == NULL) {
		fprintf(stderr, "Error: Failed to initialize MiniLibX\n");
		return 1;
	}
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fdf");
	if (fdf.win_ptr == NULL) {
		fprintf(stderr, "Error: Failed to create a window\n");
		return 1;
	}
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
