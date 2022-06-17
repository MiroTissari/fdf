/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:54:18 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/16 21:00:19 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2)
		return (error_handling(0));
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
		return (error_handling(1));
	read_map(&data, fd);
	set_values(&data);
	drawer(&data);
	hooks(&data);
	mlx_loop(data.mlx);
	return (1);
}
