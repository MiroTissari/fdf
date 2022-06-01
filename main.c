/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:54:18 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/01 15:26:13 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error_handling(int error_number)
{
	if (error_number == 0)
		write (1, "Usage: ./fdf <filename_with_map_inside>\n", 41);
	else if (error_number == 1)
		perror ("ERROR");
	else
		write (1, "what?\n", 7);
	return (0);
}

void	set_values(t_data *data)
{
	data->default_colour = WHITE;
	data->projection = ISOMETRIC;
	data->col_status = 1;
	data->big_z = 0;
	data->win_y = 1080;
	data->win_x = 1920;
	data->scale = data->win_x / (data->width * 2);
	data->elev_scale = 5;
	data->blend = 1;
	data->val_swap = 0;
	data->x_start = data->win_x / 2;
	data->y_start = data->win_y / 2;
	data->cos = 0.3;
	data->sin = 0.3;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_x, data->win_y, "fdf");
}

void	hooks(t_data *data)
{
	mlx_hook(data->win, ON_KEYUP, 0, &keyboard, data);
	mlx_hook(data->win, ON_MOUSEDOWN, 0, &mouse_hook, data);
//	mlx_hook(data->win, ON_MOUSEUP, 0, &mouse_hook, data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2)
		return (error_handling(0));
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
		return (error_handling(1));
	read_map(&data, fd);
	set_values(&data);
	drawer(&data);
	hooks(&data);
	mlx_loop(data.mlx);
	return (1);
}

/*
int	main(void)
{
	int		x;
	int		y;
	t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(data.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	y = 200;
	while (y < 1900)
	{
		x = 200;
		while (x < 300)
		{
			my_mlx_pixel_put(&img, y, x, 0xFFFF00);
			x++;
			y++;
		}
	}
	x = 210;
	while (x < 1900)
	{
		y = 510;
		while (y < 710 && x < 1900)
		{
			my_mlx_pixel_put(&img, x, y, 0xFF00FF);
			x++;
			y++;
		}
	}
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
	mlx_key_hook(data.win, close, &data);
	mlx_mouse_hook(data.win, mouse_press, &data);
	mlx_loop(data.mlx);
	free (data.mlx);
}


int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	mlx_key_hook(data.win, close, &data);
	mlx_loop(data.mlx);
	free (data.mlx);
	return (0);
}
*/
