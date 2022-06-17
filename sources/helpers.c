/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:50:48 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/16 21:00:04 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	no_blend(t_col *col1, t_col *col2, t_data *data)
{
	if (col2->color == data->default_colour
		&& col1->color != data->default_colour)
			data->col = back_to_int(col1);
	else
		data->col = back_to_int(col2);
}

int	calculate_blend(size_t col1, size_t col2, float diff)
{
	if (col1 >= col2)
			col1 = col1 - (col1 / diff);
	else
			col1 = col1 + (col2 / diff);
	if (col1 > 255)
		col1 = 255;
	return (col1);
}

int	error_handling(int error_number)
{
	if (error_number == 0)
		write (1, "Usage: ./fdf <filename_with_map_inside>\n", 41);
	else if (error_number == 1)
		perror ("ERROR");
	else if (error_number == 2)
	{
		write (1, "ERROR: invalid file\n", 21);
		exit (0);
	}
	else if (error_number == 3)
	{
		write (1, "ERROR: elevation too large\n", 28);
		exit (0);
	}
	return (0);
}
