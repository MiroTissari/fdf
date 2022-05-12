/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:33:03 by mtissari          #+#    #+#             */
/*   Updated: 2022/05/09 16:54:23 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	invalid_map(t_data *data)
{
	t_map	*temp;

	temp = data->map;
	while (data->map)
	{
		temp = data->map;
		ft_2d_free(temp->str);
		free (temp);
		data->map = data->map->next;
		data->map->next = NULL;
	}
	data->map = NULL;
	write(1, "invalid map", 12);
	exit(0);
}

t_map	*make_t_map(char *line)
{
	t_map	*map;
	int		x;

	x = 0;
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		exit (0);
	map->str = ft_strsplit (line, ' ');
	while (map->str[x])
		x++;
	map->len = x;
	map->next = NULL;
	return (map);
}

t_map	*map_helper(t_data *data, t_map *map, int i, char *line)
{
	if (i == 0)
	{
		data->map = make_t_map(line);
		map = data->map;
	}
	else
	{
		map->next = make_t_map(line);
		map = map->next;
	}
	return (map);
}

void	read_map(t_data *data, int fd)
{
	char	*line;
	t_map	*map;
	int		ret;
	int		i;

	ret = get_next_line(fd, &line);
	i = 0;
	map = NULL;
	while (ret != 0 && line[0] != '\0')
	{
		if (ret == -1)
			error_handling(1);
		map = map_helper(data, map, i, line);
		free (line);
		i++;
		if (map->len != data->map->len)
			invalid_map(data);
		ret = get_next_line(fd, &line);
	}
	close (fd);
	data->height = i;
	data->width = data->map->len;
}
