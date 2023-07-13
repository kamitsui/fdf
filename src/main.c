/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:05:41 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/13 20:39:32 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


// error.c
void	error_message(int error_code)
{
	static char	*msg[ERR_NUM] = {MSG_ARG, MSG_MLX};
	ft_fprintf(stderr, message[error_code]);
}

void	error_fdf(int error_code)
{
	error_message(error_code);
	exit(error_code);
}

void	render_fdf(t_fdf *fdf)
{


}

// initialize.c
t_map	*read_map(char *file)
{
	return (NULL);
}

void	*init_image(void *mlx)
{

	return (NULL);
}

t_fdf	*initialize_fdf(t_fdf *fdf, char *file)
{
	fdf->map = read_map(file);
	if (fdf->map == NULL)
		error_fdf(2);
		//error_fdf(ERR_MAP);
	fdf->mlx = mlx_init();
    if (fdf->mlx == NULL)
		error_fdf(3);
		//error_fdf(ERR_MLX);
	fdf->win_x = WINDOW_WIDTH;
	fdf->win_y = WINDOW_HEIGHT;
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_x, fdf->win_y, WINDOW_NAME);
	if (fdf->win == NULL)
		error_fdf(4);
		//error_fdf(ERR_WINDOW);
	fdf->image = init_image(fdf->mlx);
	if (fdf->image == NULL)
		error_fdf(5);
		//error_fdf(ERR_IMAGE);
	return (&fdf);
}


int	main(int argc, char *argv[])
{
	char	*file;
	t_fdf	fdf;
	t_image img;

	if (argc != 2)
		error_fdf(1);
		//error_fdf(ERR_ARG);
		//ft_perr_exit("Insufficient arguments. Bye!! :)\n");
	file = argv[1];
	fdf = init_fdf(file);
	fdf.img = init_image(&fdf.mlx);
	render_fdf(&fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
