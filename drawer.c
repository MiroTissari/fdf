/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:39:31 by mtissari          #+#    #+#             */
/*   Updated: 2022/05/24 19:21:45 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_drawer(int x, int y, t_data *data, int plusminus)
{
	int	math;

	if (data->next_x - x < 0)
		value_swap(data);
	x = data->cur_x;
	y = data->cur_y;
	if (data->next_y - y < 0)
		plusminus = -1;
	math = 2 * (((data->next_y - y) * plusminus) - (data->next_x - x));
	while (x <= data->next_x)
	{
		if (data->color->color != data->next_col->color && data->blend > 0)
			blend_colors(data->color, data->next_col, (data->next_x - x), data);
		my_mlx_pixel_put(data, (int)x, (int)y, data->col);
		if (math >= 0)
		{
			y = y + plusminus;
			math += 2 * (((data->next_y - y) * plusminus) - (data->next_x - x));
		}
		else
			math += 2 * ((data->next_y - y) * plusminus);
		x++;
	}
}

void	y_drawer(int x, int y, t_data *data, int plusminus)
{
	int	math;

	if (data->next_y - y < 0)
		value_swap(data);
	x = data->cur_x;
	y = data->cur_y;
	if (data->next_x - x < 0)
		plusminus = -1;
	math = 2 * (((data->next_x - x) * plusminus) - (data->next_y - y));
	while (y <= data->next_y)
	{
		if (data->color->color != data->next_col->color && data->blend > 0)
			blend_colors(data->color, data->next_col, (data->next_y - y), data);
		my_mlx_pixel_put(data, (int)x, (int)y, data->col);
		if (math >= 0)
		{
			x = x + plusminus;
			math += 2 * (((data->next_x - x) * plusminus) - (data->next_y - y));
		}
		else
			math += 2 * ((data->next_x - x) * plusminus);
		y++;
	}
}

void	get_next_data(t_data *data, t_map *line, char axis)
{
	if (axis == 'x')
	{
		data->next_x = data->x + 1;
		data->next_y = data->y;
		data->next_z = ft_atoi(line->str[data->x + 1]) * data->elev_scale;
		data->next_col = color_check(line->str[data->x + 1], data);
	}
	else if (axis == 'y')
	{
		data->next_x = data->x;
		data->next_y = data->y + 1;
		data->next_z = ft_atoi(line->next->str[data->x]) * data->elev_scale;
		data->next_col = color_check(line->next->str[data->x], data);
	}
	transform_next(data->next_x, data->next_y, data->next_z, data);
}

void	draw_to_image(t_data *data, t_map *line)
{
	int		z;

	data->color = color_check(line->str[data->x], data);
	data->col = data->color->color;
	z = ft_atoi(line->str[data->x]) * data->elev_scale;
	transform(data->cur_x, data->cur_y, z, data);
	if (line->str[data->x + 1] != '\0')
	{
		get_next_data(data, line, 'x');
		if ((data->next_x - data->cur_x) > (data->next_y - data->cur_y))
			x_drawer(data->cur_x, data->cur_y, data, 1);
		else
			y_drawer(data->cur_x, data->cur_y, data, 1);
	}
	if (line->next != NULL)
	{
		data->color = color_check(line->str[data->x], data);
		data->col = data->color->color;
		get_next_data(data, line, 'y');
		if (ft_abs(data->next_x - data->cur_x) > ft_abs(data->next_y - data->cur_y))
			x_drawer(data->cur_x, data->cur_y, data, 1);
		else
			y_drawer(data->cur_x, data->cur_y, data, 1);
	}
}

/*
	In the function above^
	first if is to draw the x_axis
	second if is to draw the y_axis
*/

int	drawer(t_data *data)
{
	t_map	*line;

	line = data->map;
	new_img(data);
	while (data->y < data->height)
	{
		data->x = 0;
		while (data->x < data->width)
		{
			data->cur_x = data->x;
			data->cur_y = data->y;
			draw_to_image(data, line);
			data->x++;
		}
		data->y++;
		line = line->next;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	return (1);
}
