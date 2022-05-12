/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:32:58 by mtissari          #+#    #+#             */
/*   Updated: 2022/05/12 21:47:23 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

# define MIN_WINDOW_X	960
# define MIN_WINDOW_Y	540
# define ESC			53

# define WHITE			0xFFFFFF
# define BLUE			0x0000FF
# define RED			0xFF0000
# define YELLOW			0xFFFF00
# define GREEN			0x00FF00
# define CYAN			0x00FFFF
# define MAGENTA		0xFF00FF

# define ISOMETRIC		34
# define PARALLEL		35

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
};

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;

	void			*mlx;
	void			*win;

	int				projection;
	float			cos;
	float			sin;
	struct s_map	*map;

	int				height;
	int				width;
	int				win_y;
	int				win_x;
	int				x_start;
	int				y_start;
	int				scale;
	int				elev_scale;

	unsigned int	default_colour;

	int				x;
	int				y;
	int				cur_x;
	int				cur_y;
	struct s_col	*color;
	unsigned int	col;

	int				next_x;
	int				next_y;
	int				next_z;
	struct s_col	*next_col;
}					t_data;

typedef struct s_map
{
	char			**str;
	int				len;
	struct s_map	*next;
}					t_map;

typedef struct s_col
{
	int				a;
	int				r;
	int				g;
	int				b;
//	char			*start;
	unsigned int	color;
}					t_col;

int		main(int argc, char **argv);
int		error_handling(int error_number);

void	read_map(t_data *data, int fd);
t_map	*make_t_map(char *line);
void	invalid_map(t_data *data);
t_map	*map_helper(t_data *data, t_map *map, int i, char *line);

void	set_values(t_data *data);

int		drawer(t_data *data);
void	draw_to_image(int x, int y, t_data *data, t_map *line);
void	get_next_data(t_data *data, t_map *line, char axis);
void	x_drawer(int x, int y, t_data *data, int plusminus);
void	y_drawer(int x, int y, t_data *data, int plusminus);

t_col	*color_check(char *str, t_data *data);
void	blend_colors(t_col *col1, t_col *col2, float diff, t_data *data);
int		calculate_blend(size_t col1, size_t col2, float diff);
void	assign_colors(t_col *col, char *str, int i, int sign);
int		back_to_int(t_col *col);

void	new_img(t_data *data);
void	transform(float x, float y, int z, t_data *data);
void	transform_next(float x, float y, int z, t_data *data);
void	value_swap(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int		ft_abs(float num);
int		hex_converter(char *hex);
char	*nb_to_hex(size_t num);
char	*hex_to_str(int hex);

int		ft_abs(float num);
int		my_close(int keycode, t_data *data);
int		mouse_press(int button, int x, int y, t_data data);

#endif
