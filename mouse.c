/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:43:12 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/01 18:01:55 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
int	left_click(int button, int x, int y, t_data data)
{
	
}
*/
int	mouse_hook(int button, int x, int y, void *param)
{
	t_data	*data;

	data = param;
	if (button == 1)
		printf("you have pressed left click at x%d y%d", x, y);
	if (button == 2)
		printf("you have pressed right click");
	if (button == 3)
		printf("you have pressed the scroll button");
	if (button == 4)
		data->scale++;
	if (button == 5)
		data->scale--;
	mlx_clear_window(data->mlx, data->win);
	drawer(data);
	return (0);
}
/*
int	mouse_down(int button, int x, int y, void *param)
{
	int		fd;
	t_data	*data;

	data = param;
	if (button == 1)
	{
		data->img = mlx_xpm_file_to_image(data->mlx, /instructions.xpm,
					&img_width, &img_height);
	}
	else if (button == 2)
	{
		
	}
	else if (button == 3)
	{
		
	}
}
*/