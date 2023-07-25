/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_points.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:18:49 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/25 19:05:40 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void	get_value(Point3D *points, int i, int j, char *token)
{
	points->x = j;
	points->y = i;
	points->z = ft_atoi((const char *)token);
}

void	set_points(char *file, Point3D **points, int rows, int cols)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	char	*token;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (i < rows)
	{
		j = 0;
		token = ft_strtok(line, DELIMITERS);
		while (j < cols)
		{
			get_value(&points[i][j], i, j, token);
			token = ft_strtok(NULL, DELIMITERS);
			j++;
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
