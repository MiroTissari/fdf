/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:10:36 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/16 16:19:30 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ft_abs(float num)
{
	int	minus;

	minus = -1;
	if (num < 0)
		num = num * minus;
	return (num);
}

void	centering(t_data *data)
{
	if (data->width < data->win_x / 10)
	{
		data->x_start = data->win_x / 2 - ((data->width * 2 * cos(0.3)) * 2);
		data->y_start = data->win_y / 2 - ((data->height * 3 * sin(0.3)) * 5);
	}
	else
	{
		data->x_start = data->win_x / 2;
		data->y_start = data->win_y / 2;
	}
}

void	set_values(t_data *data)
{
	data->default_colour = WHITE;
	data->projection = ISOMETRIC;
	data->col_status = 0;
	data->big_z = 0;
	data->win_y = 1080;
	data->win_x = 1920;
	data->scale = data->win_x / (data->width * 2);
	data->elev_scale = 5;
	data->blend = 1;
	data->menu = -1;
	data->mouse_2 = -1;
	data->mouse_3 = -1;
	data->color = (t_col *)malloc(sizeof(t_col));
	data->next_col = (t_col *)malloc(sizeof(t_col));
	if (!data->color || !data->next_col)
		exit (0);
	centering (data);
	data->val_swap = 0;
	data->cos = 0.3;
	data->sin = 0.3;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_x, data->win_y, "fdf");
}

void	hooks(t_data *data)
{
	if (data->width < 300)
	{
		mlx_hook(data->win, ON_KEYDOWN, 0, &keyboard, data);
		mlx_hook(data->win, ON_MOUSEDOWN, 0, &mouse_hook, data);
		mlx_hook(data->win, ON_MOUSEUP, 0, &mouse_hook, data);
		mlx_hook(data->win, ON_MOUSEMOVE, 0, &mouse_move, data);
	}
}
