/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:42:31 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/16 16:23:14 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	keycodes(int keycode, t_data *data)
{
	if (keycode == COL_1 || keycode == 83)
		data->col_status = 1;
	if (keycode == COL_2 || keycode == 84)
		data->col_status = 2;
	if (keycode == COL_3 || keycode == 85)
		data->col_status = 3;
	if (keycode == ELEV_PLUS || keycode == 69)
		data->elev_scale++;
	if (keycode == ELEV_MINUS || keycode == 78)
		data->elev_scale--;
	if (keycode == ISOMETRIC)
	{
		data->projection = ISOMETRIC;
		data->cos = 0.3;
		data->sin = 0.3;
		centering (data);
	}
	if (keycode == PARALLEL)
	{
		data->projection = PARALLEL;
		data->x_start = data->win_x / 2 - ((data->width * data->scale) / 2);
		data->y_start = data->win_y / 2 - ((data->height * data->scale) / 2);
	}
}

void	default_colour(t_data *data)
{
	if (data->default_colour == WHITE)
		data->default_colour = YELLOW;
	else if (data->default_colour == YELLOW)
		data->default_colour = CYAN;
	else if (data->default_colour == CYAN)
		data->default_colour = MAGENTA;
	else if (data->default_colour == MAGENTA)
		data->default_colour = GREEN;
	else if (data->default_colour == GREEN)
		data->default_colour = BLUE;
	else if (data->default_colour == BLUE)
		data->default_colour = RED;
	else if (data->default_colour == RED)
		data->default_colour = BROWN;
	else if (data->default_colour == BROWN)
		data->default_colour = WHITE;
}

int	keyboard(int keycode, void *param)
{
	t_data	*data;

	data = param;
	if (keycode == DEF_COL)
		default_colour(data);
	if (keycode == SPACE)
		data->blend *= -1;
	if (keycode == 82 || keycode == 29)
		data->col_status = 0;
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit ((int)data->mlx);
	}
	if (keycode == ELEV_MINUS || keycode == ELEV_PLUS || keycode == 69
		|| keycode == 78 || keycode == COL_1 || keycode == COL_2
		|| keycode == COL_3 || keycode == 83 || keycode == 84
		|| keycode == 85 || keycode == ISOMETRIC || keycode == PARALLEL)
		keycodes(keycode, data);
	mlx_clear_window(data->mlx, data->win);
	drawer(data);
	return (0);
}
