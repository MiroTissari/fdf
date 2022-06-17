/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:32:58 by mtissari          #+#    #+#             */
/*   Updated: 2022/06/17 12:27:19 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

# define WHITE			0xFFFFFF
# define BLUE			0x0000FF
# define RED			0xFF0000
# define YELLOW			0xFFFF00
# define GREEN			0x00FF00
# define CYAN			0x00FFFF
# define MAGENTA		0xFF00FF
# define BROWN			0xA52A2A

# define ESC			53
# define ISOMETRIC		34
# define PARALLEL		35
# define SPACE			49
# define COL_1			18
# define COL_2			19
# define COL_3			20
# define DEF_COL		8
# define ELEV_PLUS		24
# define ELEV_MINUS		27

# define ON_KEYDOWN		2
# define ON_KEYUP		3
# define ON_MOUSEDOWN	4
# define ON_MOUSEUP		5
# define ON_MOUSEMOVE	6
# define ON_EXPOSE		12
# define ON_DESTROY		17

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	void			*mlx;
	void			*win;

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

	int				x;
	int				y;
	int				z;
	int				big_z;
	int				cur_x;
	int				cur_y;
	int				next_x;
	int				next_y;
	int				next_z;

	struct s_col	*color;
	int				col;
	int				blend;
	struct s_col	*next_col;

	int				default_colour;
	int				col_status;
	int				val_swap;
	int				projection;
	int				mouse_x;
	int				mouse_y;
	int				menu;
	int				mouse_2;
	int				mouse_3;
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
	int				color;
}					t_col;

int		main(int argc, char **argv);

void	read_map(t_data *data, int fd);
t_map	*make_t_map(char *line, t_data *data);
void	invalid_map(t_data *data);
t_map	*map_helper(t_data *data, t_map *map, int i, char *line);
void	check_validity(char *line, t_data *data);

int		drawer(t_data *data);
void	draw_to_image(t_data *data, t_map *line);
void	get_next_data(t_data *data, t_map *line, char axis);
void	x_drawer(int x, int y, t_data *data, int plusminus);
void	y_drawer(int x, int y, t_data *data, int plusminus);

void	new_img(t_data *data);
void	transform(float x, float y, int z, t_data *data);
void	transform_next(float x, float y, int z, t_data *data);
void	value_swap(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int		ft_abs(float num);
void	centering(t_data *data);
void	set_values(t_data *data);
void	hooks(t_data *data);

void	color_check(char *str, t_data *data);
void	color_check_next(char *str, t_data *data);
void	blend_colors(t_col *col1, t_col *col2, float diff, t_data *data);
void	assign_colors(t_col *col, char *str, int i, int sign);
t_col	*color_altitude(char *str, t_col *col, t_data *data);

int		hex_converter(char *hex);
char	*nb_to_hex(size_t num);
char	*hex_to_str(int hex);
int		back_to_int(t_col *col);

void	no_blend(t_col *col1, t_col *col2, t_data *data);
int		calculate_blend(size_t col1, size_t col2, float diff);
int		error_handling(int error_number);

int		mouse_hook(int button, int x, int y, void *param);
int		mouse_move(int x, int y, void *param);
void	clear_and_draw(t_data *data);
void	print_menu(t_data *data);

int		keyboard(int keycode, void *param);
void	keycodes(int keycode, t_data *data);
void	default_colour(t_data *data);

#endif
