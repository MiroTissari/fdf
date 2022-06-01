/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:42:31 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/01 18:11:13 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	colour_elev(int keycode, t_data *data)
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
	}
	if (keycode == PARALLEL)
	{
		data->projection = PARALLEL;
	}
	if (keycode == SPACE)
		data->blend *= -1;
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
		data->default_colour = WHITE;
}

int	keyboard(int keycode, void *param)
{
	t_data	*data;

	data = param;
	if (keycode == DEF_COL)
		default_colour(data);
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit ((int)data->mlx);
	}
	if (keycode == ELEV_MINUS || keycode == ELEV_PLUS || keycode == 69
		|| keycode == 78 || keycode == COL_1 || keycode == COL_2
		|| keycode == COL_3 || keycode == 83 || keycode == 84
		|| keycode == 85 || keycode == 49 || keycode == ISOMETRIC
		|| keycode == PARALLEL)
		colour_elev(keycode, data);
	mlx_clear_window(data->mlx, data->win);
	drawer(data);
	return (0);
}
