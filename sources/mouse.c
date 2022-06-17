/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:43:12 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/09 21:09:26 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	print_menu(t_data *data)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = data->mlx;
	win = data->win;
	mlx_string_put(mlx, win, 70, y += 20, CYAN, "Instructions: How to use");
	mlx_string_put(mlx, win, 15, y += 35, MAGENTA, "Mouse:");
	mlx_string_put(mlx, win, 60, y += 35, WHITE, "Press and hold left button \
		for instructions");
	mlx_string_put(mlx, win, 60, y += 35, WHITE, "Press and hold right button \
		to rotate the isometric projection");
	mlx_string_put(mlx, win, 60, y += 35, WHITE, "Zoom: Scroll up or down");
	mlx_string_put(mlx, win, 15, y += 35, MAGENTA, "Keyboard:");
	mlx_string_put(mlx, win, 60, y += 30, WHITE, "elevation +/-: press '+/-'");
	mlx_string_put(mlx, win, 45, y += 30, YELLOW, "Projection:");
	mlx_string_put(mlx, win, 60, y += 25, WHITE, "ISO: 'I', Parallel: 'P'");
	mlx_string_put(mlx, win, 45, y += 25, YELLOW, "Change colours to:");
	mlx_string_put(mlx, win, 60, y += 25, WHITE, "Default color: press '0'");
	mlx_string_put(mlx, win, 60, y += 25, WHITE, "From the map: press '1'");
	mlx_string_put(mlx, win, 60, y += 25, WHITE, "Mountain: press '2'");
	mlx_string_put(mlx, win, 60, y += 25, WHITE, "Red at top: press '3'");
	mlx_string_put(mlx, win, 60, y += 25, WHITE, "Change default: press 'c'");
	mlx_string_put(mlx, win, 60, y += 25, WHITE, "Blending y/n: press 'Space'");
	mlx_string_put(mlx, win, 45, y += 25, YELLOW, "Close program: press 'esc'");
}

void	clear_and_draw(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	drawer(data);
}

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;

	data = param;
	if (data->mouse_2 > 0)
	{
		if (data->mouse_x > x)
			data->cos += 0.010;
		if (data->mouse_x < x)
			data->cos -= 0.010;
		if (data->mouse_y > y)
			data->sin += 0.010;
		if (data->mouse_y < y)
			data->sin -= 0.010;
		clear_and_draw(data);
		data->mouse_x = x;
		data->mouse_y = y;
	}
	if (data->mouse_3 > 0)
	{
		data->y_start = y;
		data->x_start = x;
		clear_and_draw(data);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data	*data;

	data = param;
	if (button == 2)
		data->mouse_2 *= -1;
	if (button == 3)
		data->mouse_3 *= -1;
	if (button == 1 || button == 4 || button == 5)
	{
		if (button == 1)
			data->menu *= -1;
		if (button == 4)
			data->scale++;
		if (button == 5)
			data->scale--;
		mlx_clear_window(data->mlx, data->win);
		drawer(data);
	}
	x += 0;
	y += 0;
	return (0);
}
