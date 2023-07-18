/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:09:35 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/18 18:53:46 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ft_printf.h"

#define WIN_WIDTH 1000  // Width of the window
#define WIN_HEIGHT 800 // Height of the window
#define IMG_WIDTH 800  // Width of the window
#define IMG_HEIGHT 600 // Height of the window
#define TILE_SIZE 15   // Size of each tile
#define COLOR 0xFFFFFF // Color value for points and lines (white)
#define OFFSET_X 300
#define OFFSET_Y 150
#define KEY_ESC 0xff1b
//#define KEY_ESC 53

// man keysyms
//Escape                           65307     0xff1b

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
    void *mlx_ptr;      // MiniLibX graphics system pointer
    void *win_ptr;      // Window pointer
	t_data	*data;		// Image pointer
    Point3D **points;   // 2D array to store the points
	Map map;
} t_fdf;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	my_key_function(int keycode, t_fdf *fdf)
{
    // Get the window pointer from the parameter
    void *mlx_ptr = fdf->mlx_ptr;
    void *win_ptr = fdf->win_ptr;
	void *img = fdf->data->img;
	Point3D **points = fdf->points;
	int rows = fdf->map.rows;

    // Check if the ESC key (keycode 53) was pressed
    //if (keycode == 53)
    if (keycode == KEY_ESC)
    {
	    // Clean up resources and exit
	    for (int i = 0; i < rows; i++) {
	        free(points[i]);
	    }
	    free(points);
        // Close the window and the program
	    mlx_destroy_window(mlx_ptr, win_ptr);
	    mlx_destroy_image(mlx_ptr, img);
    }
	exit(0);
}

//void mlx_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        // Set the pixel color at the current position (x0, y0)
        //mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);
		my_mlx_pixel_put(data, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int err2 = 2 * err;

        if (err2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (err2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

//void draw_wireframe_model(void *mlx_ptr, void *win_ptr, Point3D **points, int rows, int cols)
void draw_wireframe_model(t_data *data, Point3D **points, int rows, int cols)
{
    // Loop through the points and draw the wireframe model
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Point3D current_point = points[i][j];

            // Calculate the screen coordinates using isometric projection
            //int screen_x = (current_point.x - current_point.y) * TILE_SIZE;
            //int screen_y = (current_point.x + current_point.y) * TILE_SIZE - current_point.z * TILE_SIZE;
            int screen_x = (current_point.x - current_point.y) * TILE_SIZE + OFFSET_X;
            int screen_y = (current_point.x + current_point.y) * TILE_SIZE - current_point.z * TILE_SIZE + OFFSET_Y;

            // Draw the point
            //mlx_pixel_put(mlx_ptr, win_ptr, screen_x, screen_y, COLOR);
            my_mlx_pixel_put(data, screen_x, screen_y, COLOR);

            // Connect adjacent points with lines to create the wireframe
            if (j < cols - 1) {
                Point3D next_point = points[i][j + 1];
                //int next_screen_x = (next_point.x - next_point.y) * TILE_SIZE;
                //int next_screen_y = (next_point.x + next_point.y) * TILE_SIZE - next_point.z * TILE_SIZE;
                int next_screen_x = (next_point.x - next_point.y) * TILE_SIZE + OFFSET_X;
                int next_screen_y = (next_point.x + next_point.y) * TILE_SIZE - next_point.z * TILE_SIZE + OFFSET_Y;
                //mlx_line(mlx_ptr, win_ptr, screen_x, screen_y, next_screen_x, next_screen_y, COLOR);
                draw_line(data, screen_x, screen_y, next_screen_x, next_screen_y, COLOR);
            }
            if (i < rows - 1) {
                Point3D next_point = points[i + 1][j];
                //int next_screen_x = (next_point.x - next_point.y) * TILE_SIZE;
                //int next_screen_y = (next_point.x + next_point.y) * TILE_SIZE - next_point.z * TILE_SIZE;
                int next_screen_x = (next_point.x - next_point.y) * TILE_SIZE + OFFSET_X;
                int next_screen_y = (next_point.x + next_point.y) * TILE_SIZE - next_point.z * TILE_SIZE + OFFSET_Y;
                //mlx_line(mlx_ptr, win_ptr, screen_x, screen_y, next_screen_x, next_screen_y, COLOR);
                draw_line(data, screen_x, screen_y, next_screen_x, next_screen_y, COLOR);
            }
        }
    }
}

int main(int ac, char *av[])
{
	t_fdf	fdf;
	t_data	data;
	fdf.data = &data;
//    void *mlx_ptr;      // MiniLibX graphics system pointer
//    void *win_ptr;      // Window pointer
    Point3D **points;   // 2D array to store the points
    int rows, cols;     // Number of rows and columns in the map

	if (ac != 2)
	{
		printf("argument 2\n");
		return -1;
	}

    // Open the file and read the map dimensions
    FILE *file = fopen(av[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Failed to open the file\n");
        return 1;
    }
    //fscanf(file, "%d %d\n", &rows, &cols);
	fdf.map.rows = 11;
	fdf.map.cols = 19;
	rows = fdf.map.rows;
	cols = fdf.map.cols;

    // Allocate memory for the points array
    points = (Point3D **)malloc(rows * sizeof(Point3D *));
    if (points == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        fclose(file);
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        points[i] = (Point3D *)malloc(cols * sizeof(Point3D));
        if (points[i] == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory\n");
            fclose(file);
            return 1;
        }
    }
	fdf.points = points;

    // Read the points from the file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &points[i][j].z);
            points[i][j].x = j;
            points[i][j].y = i;
			//printf("[%d][%d].z : %d   ", i, j, points[i][j].z);
        }
		//printf("\n");
    }
    fclose(file);

    // Initialize the MiniLibX graphics system
    fdf.mlx_ptr = mlx_init();
    if (fdf.mlx_ptr == NULL) {
        fprintf(stderr, "Error: Failed to initialize MiniLibX\n");
        return 1;
    }

    // Create a new window
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fdf");
    if (fdf.win_ptr == NULL) {
        fprintf(stderr, "Error: Failed to create a window\n");
        return 1;
    }

	// Clear window
	//mlx_clear_window(mlx_ptr, win_ptr);
	//exit(1);

	// Create a new image
	data.img = mlx_new_image(fdf.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);

	// Get the image data address and information
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.size_line,
								&data.endian);

	// Output the retrieved information
	printf("Bits per pixel: %d\n", data.bits_per_pixel);
	printf("Size of each line: %d bytes\n", data.size_line);
	printf("Endianness: %d\n", data.endian);

	// Set pixel
	//my_mlx_pixel_put(&data, 5, 5, 0x00FF0000);
	//draw_line(&data, 0, 0, 100, 200, 0x00FFFFFF);

    // Draw the wireframe model
    //draw_wireframe_model(mlx_ptr, win_ptr, points, rows, cols);
    draw_wireframe_model(&data, points, rows, cols);

	// Put pixel
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, data.img, 100, 100);

    // Set up the keyboard hook for the window
    mlx_key_hook(fdf.win_ptr, &my_key_function, &fdf);

    // Start the event loop
    mlx_loop(fdf.mlx_ptr);


    // Clean up resources and exit
    for (int i = 0; i < rows; i++) {
        free(points[i]);
    }
    free(points);
//    mlx_destroy_window(fdf.mlx_ptr, fdf.win_ptr);
//    mlx_destroy_image(fdf.mlx_ptr, data.img);
}

