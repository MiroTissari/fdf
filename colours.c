/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:07:55 by mtissari          #+#    #+#             */
/*   Updated: 2022/05/12 21:53:25 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
}

t_col	*color_check(char *str, t_data *data)
{
	int		i;
	t_col	*col;

	i = 0;
	col = (t_col *)malloc(sizeof(t_col));
	while (str[i] != ',' && str[i])
		i++;
	if (str[i] == ',')
	{
		if (ft_strlen(&str[i + 1]) == 10)
			assign_colors(col, str, i, 1);
		else if (ft_strlen(&str[i + 1]) == 8)
			assign_colors(col, str, i, 2);
		col->color = back_to_int(col);
		return (col);
	}
	col->color = data->default_colour;
	assign_colors(col, hex_to_str(data->default_colour), 0, 3);
	return (col);
}

void	blend_colors(t_col *col1, t_col *col2, float diff, t_data *data)
{
	if (col1)
	{
		if (col1->r != col2->r)
			col1->r = calculate_blend(col1->r, col2->r, diff);
		if (col1->g != col2->g)
			col1->g = calculate_blend(col1->g, col2->g, diff);
		if (col1->b != col2->b)
			col1->b = calculate_blend(col1->b, col2->b, diff);
		data->col = back_to_int(col1);
	}
}

int	back_to_int(t_col *col)
{
	char	*str;

	str = ft_strnew (7);
	if (col->r != 0)
		str = nb_to_hex(col->r);
	else
	{
		str[0] = '0';
		str[1] = '0';
	}
	if (col->g != 0)
		str = ft_strjoin(str, nb_to_hex(col->g));
	else
	{
		str[2] = '0';
		str[3] = '0';
	}
	if (col->b != 0)
		str = ft_strjoin(str, nb_to_hex(col->b));
	else
	{
		str[4] = '0';
		str[5] = '0';
	}
	return (hex_converter(str));
}

int	calculate_blend(size_t col1, size_t col2, float diff)
{
	if (col1 >= col2)
			col1 = col1 - (col1 / diff);
	else
			col1 = col1 + (col2 / diff);
	return (col1);
}

/*
	blend = col1;
	if (col1 == WHITE)
	{
		blend = col1
	}
	else if (col1 > col2)
	{
		blend = (int)col1 - ((col1 - col2) / diff);
	}
	else if (col2 > col1)
	{
		blend = col1 + ((col2 - col1) / diff);
	}
	data->col = blend;
}
*/
