/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:40:33 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/19 14:56:04 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>// for fprintf

void	read_map(char *file, t_fdf *fdf)
//void	read_map(FILE *file, t_fdf *fdf)
{
	Point3D **points;
	points = fdf->points;
	int rows, cols;     // Number of rows and columns in the map
	//int fd = open(file, O_RDONLY);
	FILE *file_ptr = fopen(file, O_RDONLY);
	//if (fd == -1) {
	if (file_ptr == NULL) {
		ft_perror_exit("open");
		//fprintf(stderr, "Error: Failed to open the file\n");
		//return 1;
	}
	fscanf(file_ptr, "%d %d\n", &rows, &cols);
	fdf->map.rows = 11;
	fdf->map.cols = 19;
	rows = fdf->map.rows;
	cols = fdf->map.cols;

	// Allocate memory for the points array
	points = (Point3D **)malloc(rows * sizeof(Point3D *));
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
