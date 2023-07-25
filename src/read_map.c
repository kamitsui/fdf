/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:40:33 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/25 18:43:35 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void	count_width_depth(int fd, char *line, int *width, int *depth)
{
	int		pre_width;

	*width = ft_count_words(line, ' ');
	pre_width = *width;
	*depth = *depth + 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		*width = ft_count_words(line, ' ');
		if (pre_width != *width)
			error_fdf(ERR_MAP);
		if (ft_isprint(*line) == true)
			*depth = *depth + 1;
		free(line);
	}
}

static	void	get_rows_cols(char *file, int *rows, int *cols)
{
	int		fd;
	char	*line;
	int		width;
	int		depth;

	width = 0;
	depth = 0;
	if (access(file, F_OK | R_OK) == -1)
		ft_errno_exit(file);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return ;
	count_width_depth(fd, line, &width, &depth);
	free(line);
	close(fd);
	*rows = depth;
	*cols = width;
	return ;
}

static Point3D	**allocate_points(int rows, int cols)
{
	Point3D	**points;
	int		i;

	points = (Point3D **)malloc(rows * sizeof(Point3D *));
	if (points == NULL)
		ft_errno_exit("malloc");
	i = 0;
	while (i < rows)
	{
		points[i] = (Point3D *)malloc(cols * sizeof(Point3D));
		if (points[i] == NULL)
			ft_errno_exit("malloc");
		i++;
	}
	return (points);
}

//void	get_value(Point3D points, int i, int j, char *token)
//{
//	points.x = j;
//	points.y = i;
//	points.z = atoi(token);
//}
//
//void	set_points(char *file, Point3D **points, int rows, int cols)
//{
//	int		fd;
//	char	*line;
//	int		i;
//	int		j;
//	char	*token;
//
//	fd = open(file, O_RDONLY);
//	line = get_next_line(fd);
//	i = 0;
//	while (i < rows)
//	{
//		j = 0;
//		token = ft_strtok(line, DELIMITERS);
//		while (j < cols)
//		{
//			get_value(points[i][j], i, j, token);
//			token = ft_strtok(NULL, DELIMITERS);
//			j++;
//		}
//		free(line);
//		line = get_next_line(fd);
//		i++;
//	}
//	close(fd);
//}
//			points[i][j].x = j;
//			points[i][j].y = i;
//			points[i][j].z = atoi(token);

void	read_map(char *file, t_fdf *fdf)
{
	get_rows_cols(file, &fdf->map->rows, &fdf->map->cols);
	fdf->points = allocate_points(fdf->map->rows, fdf->map->cols);
	set_points(file, fdf->points, fdf->map->rows, fdf->map->cols);
}
