/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:50:48 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/01 17:55:27 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	no_blend(t_col *col1, t_col *col2, t_data *data)
{
	data->col = back_to_int(col2);
	if (col2->color == data->default_colour
		&& col1->color != data->default_colour)
			data->col = back_to_int(col1);
}
