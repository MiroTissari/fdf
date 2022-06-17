/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:33:03 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/16 21:00:13 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	invalid_map(t_data *data)
{
	t_map	*temp;

	while (data->map)
	{
		temp = data->map;
		ft_2d_free(temp->str);
		data->map = data->map->next;
		free (temp);
		temp = NULL;
	}
	data->map = NULL;
	write(1, "invalid map\n", 13);
	exit(0);
}

void	check_validity(char *line, t_data *data)
{
	int	x;
	int	not_nb;

	x = 0;
	not_nb = 0;
	while (line[x] != '\0')
	{
		if (!ft_isdigit(line[x]))
		{
			if (line[x] != '-' && line[x] != ',' && line[x] != ' '
				&& line[x] != 'x' && line[x] != '\n')
			{
				if ((line[x] < 'A' || line[x] > 'F')
					&& (line[x] < 'a' || line[x] > 'f'))
					invalid_map(data);
			}
			not_nb++;
		}
		x++;
	}
	if (not_nb == x || x == 0)
		invalid_map(data);
}

t_map	*make_t_map(char *line, t_data *data)
{
	t_map	*map;
	int		x;
	int		i;

	x = 0;
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		exit (0);
	map->str = ft_strsplit (line, ' ');
	while (map->str[x])
	{
		i = 0;
		while (map->str[x][i] != ',' && map->str[x][i] != '\0')
		{
			if (!ft_isdigit(map->str[x][i]) && map->str[x][0] != '-')
				invalid_map(data);
			i++;
		}
		x++;
	}
	map->len = x;
	map->next = NULL;
	return (map);
}

t_map	*map_helper(t_data *data, t_map *map, int i, char *line)
{
	check_validity(line, data);
	if (i == 0)
	{
		data->map = make_t_map(line, data);
		map = data->map;
	}
	else
	{
		map->next = make_t_map(line, data);
		map = map->next;
		if (map->len != data->map->len)
			invalid_map(data);
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
	data->map = NULL;
	while (ret != 0)
	{
		if (ret == -1)
			error_handling(1);
		map = map_helper(data, map, i, line);
		free (line);
		i++;
		ret = get_next_line(fd, &line);
	}
	close (fd);
	if (i == 0)
		invalid_map(data);
	data->height = i;
	data->width = data->map->len;
	if (data->height == 1 && data->width == 1)
		invalid_map(data);
}
