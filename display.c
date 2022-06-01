/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:44:37 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/01 15:24:12 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	new_img(t_data *data)
{
	data->img = mlx_new_image(data->mlx, data->win_x, data->win_y);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->x = 0;
	data->y = 0;
}

void	transform(float x, float y, int z, t_data *data)
{
	float	temp_x;

	x *= data->scale;
	y *= data->scale;
	temp_x = x;
	if (z > data->big_z)
		data->big_z = z;
	if (data->projection == ISOMETRIC)
	{
		x = (temp_x - y) * cos(data->cos);
		y = (temp_x + y) * sin(data->sin) - z;
	}
	data->cur_x = x + data->x_start;
	data->cur_y = y + data->y_start;
}

void	transform_next(float x, float y, int z, t_data *data)
{
	float	temp_x;

	x *= data->scale;
	y *= data->scale;
	temp_x = x;
	if (data->projection == ISOMETRIC)
	{
		x = (temp_x - y) * cos(data->cos);
		y = (temp_x + y) * sin(data->sin) - z;
	}
	data->next_x = x + data->x_start;
	data->next_y = y + data->y_start;
}

void	value_swap(t_data *data)
{
	float	temp;
	t_col	*tempo;

	temp = data->cur_x;
	data->cur_x = data->next_x;
	data->next_x = temp;
	temp = data->cur_y;
	data->cur_y = data->next_y;
	data->next_y = temp;
	tempo = data->color;
	data->color = data->next_col;
	data->next_col = tempo;
	if (data->val_swap == 1)
		data->val_swap = 0;
	else
		data->val_swap = 1;
}
