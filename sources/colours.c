/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:07:55 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/16 18:16:52 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	assign_colors(t_col *col, char *str, int i, int sign)
{
	if (sign == 1)
	{
		col->a = hex_converter(ft_strsub(&str[i + 3], 0, 2));
		col->r = hex_converter(ft_strsub(&str[i + 5], 0, 2));
		col->g = hex_converter(ft_strsub(&str[i + 7], 0, 2));
		col->b = hex_converter(ft_strsub(&str[i + 9], 0, 2));
	}
	else if (sign == 2)
	{
		col->r = hex_converter(ft_strsub(&str[i + 3], 0, 2));
		col->g = hex_converter(ft_strsub(&str[i + 5], 0, 2));
		col->b = hex_converter(ft_strsub(&str[i + 7], 0, 2));
	}
	else
	{
		col->r = hex_converter(ft_strsub(&str[i], 0, 2));
		col->g = hex_converter(ft_strsub(&str[i + 2], 0, 2));
		col->b = hex_converter(ft_strsub(&str[i + 4], 0, 2));
	}
	col->color = back_to_int(col);
}

void	color_check(char *str, t_data *data)
{
	int		i;

	i = 0;
	while (str[i] != ',' && str[i] && data->col_status != 0)
		i++;
	if (str[i] == ',' && str[i + 1] && data->col_status == 1)
	{
		if (ft_strlen(&str[i + 1]) == 10)
			assign_colors(data->color, str, i, 1);
		else if (ft_strlen(&str[i + 1]) == 8)
			assign_colors(data->color, str, i, 2);
		else
			assign_colors(data->color, hex_to_str(data->default_colour), 0, 5);
	}
	else if (data->col_status == 2 || data->col_status == 3)
		data->color = color_altitude(str, data->color, data);
	else
		assign_colors(data->color, hex_to_str(data->default_colour), 0, 5);
	data->col = data->color->color;
}

void	color_check_next(char *str, t_data *data)
{
	int		i;

	i = 0;
	while (str[i] != ',' && str[i] && data->col_status != 0)
		i++;
	if (str[i] == ',' && str[i + 1] && data->col_status == 1)
	{
		if (ft_strlen(&str[i + 1]) == 10)
			assign_colors(data->next_col, str, i, 1);
		else if (ft_strlen(&str[i + 1]) == 8)
			assign_colors(data->next_col, str, i, 2);
	}
	else if (data->col_status == 2 || data->col_status == 3)
		data->next_col = color_altitude(str, data->next_col, data);
	else
		assign_colors(data->next_col, hex_to_str(data->default_colour), 0, 5);
}

t_col	*color_altitude(char *str, t_col *col, t_data *data)
{
	int	alt;

	alt = ft_atoi(str) * data->elev_scale;
	if (data->col_status == 2)
	{
		if (alt > 0)
		{
			if (alt < (data->big_z / 3 * 2))
				assign_colors(col, hex_to_str(BROWN), 0, 5);
			else
				assign_colors(col, hex_to_str(WHITE), 0, 5);
		}
		else
			assign_colors(col, hex_to_str(GREEN), 0, 5);
	}
	if (data->col_status == 3)
	{
		if (alt != 0)
			assign_colors(col, hex_to_str(RED), 0, 5);
		else
			assign_colors(col, hex_to_str(data->default_colour), 0, 5);
	}
	return (col);
}

void	blend_colors(t_col *col1, t_col *col2, float diff, t_data *data)
{
	if (data->col_status == 2 && data->blend > 0)
	{
		if (diff < 0)
			diff *= -1;
		if (diff > 2 * data->elev_scale && diff > 30)
			assign_colors(col2, hex_to_str(BROWN), 0, 5);
		else
		{
			assign_colors(col2, hex_to_str(WHITE), 0, 5);
			if ((data->next_z <= 0 && data->val_swap == 0)
				|| (data->z <= 0 && data->val_swap == 1))
				assign_colors(col2, hex_to_str(GREEN), 0, 5);
		}
		diff = diff / 3;
	}
	if (col1->r != col2->r && data->blend > 0)
		col1->r = calculate_blend(col1->r, col2->r, diff);
	if (col1->g != col2->g && data->blend > 0)
		col1->g = calculate_blend(col1->g, col2->g, diff);
	if (col1->b != col2->b && data->blend > 0)
		col1->b = calculate_blend(col1->b, col2->b, diff);
	data->col = back_to_int(col1);
	if (data->blend < 0)
		no_blend(col1, col2, data);
}
