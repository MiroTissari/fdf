/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:07:55 by mtissari          #+#    #+#             */
/*   Updated: 2022/05/12 19:55:06 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	assign_colors(t_col *col, char *str, int i, int sign)
{
	if (sign == 1)
	{
	//	col->start = ft_strsub(&str[i + 1], 0, 2);
		col->a = hex_converter(ft_strsub(&str[i + 3], 0, 2));
		col->r = hex_converter(ft_strsub(&str[i + 5], 0, 2));
		col->g = hex_converter(ft_strsub(&str[i + 7], 0, 2));
		col->b = hex_converter(ft_strsub(&str[i + 9], 0, 2));
	}
	else if (sign == 2)
	{
	//	col->start = (ft_strsub(&str[i + 1], 0, 2));
		//printf("start: %d\n", col->start);
	//	col->a = 255;
		col->r = hex_converter(ft_strsub(&str[i + 3], 0, 2));
		col->g = hex_converter(ft_strsub(&str[i + 5], 0, 2));
		col->b = hex_converter(ft_strsub(&str[i + 7], 0, 2));
	}
}

t_col	*color_check(char *str, t_data *data)
{
	int		i;
	t_col	*col;
	//char	*temp;

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
		//temp = ft_strjoin(ft_itoa(col->a), ft_itoa(col->r));
		//temp = ft_strjoin(temp, ft_itoa(col->g));
		//temp = ft_strjoin(temp, ft_itoa(col->b));
		col->color = back_to_int(col);
		//free (temp);
		i = col->color;
	//	printf("color: %d\t", i);
		printf("col->r: %d\t", col->r);
		printf("col->g: %d\t", col->g);
		printf("col->b: %d\n", col->b);
		return (col);
	}
	col->color = data->default_colour;
	return (col);
}

void	blend_colors(t_col *col1, t_col *col2, float diff, t_data *data)
{
	//printf("col->r: %d\t", col1->r);
	//printf("col->g: %d\t", col1->g);
	//printf("col->b: %d\n", col1->b);
	if (col1)
	{
		if (col1->a != col2->a)
			col1->a = calculate_blend(col1->a, col2->a, diff);
		if (col1->r != col2->r)
			col1->r = calculate_blend(col1->r, col2->r, diff);
		if (col1->g != col2->g)
			col1->g = calculate_blend(col1->g, col2->g, diff);
		if (col1->b != col2->b)
			col1->b = calculate_blend(col1->b, col2->b, diff);
		//printf("after col->r: %d\t", col1->r);
		//printf("after col->g: %d\t", col1->g);
		//printf("after col->b: %d\n", col1->b);
		data->col = back_to_int(col1);
	}
}

int	back_to_int(t_col *col)
{
	char	*str;

	
	str = ft_strnew (6);
	ft_bzero (str, 6);
	if (col->r != 0)
		str = nb_to_hex(col->r);
	else
	{
		str[0] = '0';
		str[1] = '0';
	}
	//printf("red: %s\t", str);
	if (col->g != 0)
		ft_strjoin(str, nb_to_hex(col->g));
	else
	{
		str[2] = '0';
		str[3] = '0';
	}
	//printf("red & green: %s\t", str);
	if (col->b != 0)
		ft_strjoin(str, nb_to_hex(col->b));
	else
	{
		str[4] = '0';
		str[5] = '0';
	}
	//printf("All: %s\t", str);
	return (hex_converter(str));
}

int	calculate_blend(int col1, int col2, float diff)
{
//	printf ("col2: %d\t", col2);
//	printf ("diff: %f\t", diff);
//	printf ("col1 before: %d\t", col1);
	if (col1 > col2)
			col1 = col1 - (col1 / diff);
	else
			col1 = col1 + (col2 / diff);
//	printf ("col1 after: %d\t", col1);
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
