/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:40:33 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/24 23:18:40 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>// for fprintf

static	void	get_rows_cols(char *file, int *rows, int *cols)
{
	int		fd;
	char	*line;
	int		width;
	int		pre_width;
	int		depth;

	width = 0;
	depth = 0;
	if (access(file, F_OK | R_OK) == -1)
		ft_errno_exit(file);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return ;
	width = ft_count_words(line, ' ');
	pre_width = width;
	depth++;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		width = ft_count_words(line, ' ');
		if (pre_width != width)
			ft_perror_exit("Noooo!!\n");
		if (ft_isprint(*line) == true)
			depth++;
		free(line);
	}
	free(line);
	close(fd);
	*rows = depth;
	*cols = width;
	return ;
}

Point3D	**init_points(char *file, t_fdf *fdf)
{
	if (file == NULL || fdf == NULL)
		exit(1);
	return (NULL);
}

Point3D	**extract_coordinate(char *file, t_fdf *fdf)
{
	if (file == NULL || fdf == NULL)
		exit(1);
	return (NULL);
}

static void	read_map_provisional(char *file, t_fdf *fdf);// debug

void	read_map(char *file, t_fdf *fdf)
{
	read_map_provisional(file, fdf);
	//get_rows_cols(file, &fdf->map->rows, &fdf->map->cols);
	//fdf->map->cols = get_cols(file);
	//fdf->points = init_points(file, fdf);
	//fdf->points = extract_coordinate(file, fdf);
//	map->coordinates = init_coordinates(map->max_x, map->max_y);
//	if (!map->coordinates)
//	{
//		free(map);
//		return (NULL);
//	}
//	get_points(file_name, map);
//	center_to_origin(map);
//	return (map);
}


static void	read_map_provisional(char *file, t_fdf *fdf)
{
	Point3D **points;
	//points = fdf->points;
	int rows, cols;     // Number of rows and columns in the map
	//int fd = open(file, O_RDONLY);
	FILE *file_ptr = fopen(file, "r");
//	//if (fd == -1) {
	if (file_ptr == NULL) {
		ft_perror_exit("open");
		//fprintf(stderr, "Error: Failed to open the file\n");
		//return 1;
	}
//	//fscanf(file_ptr, "%d %d\n", &rows, &cols);
//	//printf("%d %d\n", rows, cols);
//	//exit(0);
//	fdf->map->rows = 11;
//	fdf->map->cols = 19;
	get_rows_cols(file, &fdf->map->rows, &fdf->map->cols);
	rows = fdf->map->rows;
	cols = fdf->map->cols;


	// Allocate memory for the points array
	points = (Point3D **)malloc(rows * sizeof(Point3D *));
	fdf->points = points;
	if (points == NULL) {
		//close(fd);
		fclose(file_ptr);
		ft_perror_exit("malloc");
		//fprintf(stderr, "Error: Failed to allocate memory\n");
		//return 1;
	}
	for (int i = 0; i < rows; i++) {
		points[i] = (Point3D *)malloc(cols * sizeof(Point3D));
		if (points[i] == NULL) {
			//close(fd);
			fclose(file_ptr);
			ft_perror_exit("malloc");
			//fprintf(stderr, "Error: Failed to allocate memory\n");
			//return 1;
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fscanf(file_ptr, "%d", &points[i][j].z);
			points[i][j].x = j;
			points[i][j].y = i;
			//printf("[%d][%d].z : %d   ", i, j, points[i][j].z);
		}
		//printf("\n");
	}
	//close(fd);
	fclose(file_ptr);
}

