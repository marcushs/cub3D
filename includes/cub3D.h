/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:22:33 by hleung            #+#    #+#             */
/*   Updated: 2023/10/17 11:01:31 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# define INV_ID "Error:\nInvalid identifier!\n"
# define INV_EXT "Error:\nInvalid file extension (expected `.cub')!\n"
# define MAP_LAST "Error:\nMap content misplaced or missing element!\n"
# define NO_PATH "Error:\nNo path or value specified!\n"
# define MUL_PATH "Error:\nMore than one path specified!\n"
# define NB_VALUE "Error:\nWrong number of RGB values!\n"
# define NON_NUM "Error:\nOnly numerical values allowed!\n"
# define OUT_RANGE "Error:\nValue out of range!\n"
# define NO_MAP "Error:\nNo map given!\n"
# define MAP_EMPTY "Error:\nEmpty line in map content!\n"
# define INV_CHAR "Error:\nInvalid character in map!\n"
# define POV_ERR "Error:\nNeed one and only one player in map!\n"
# define WALL_ERR "Error:\nMap not enclosed by wall!\n"
# define MALLOC_ERR "Malloc error!\n"
# define XK_w 119
# define XK_d 100
# define XK_s 115
# define XK_a 97
# define XK_left 65361
# define XK_right 65363
# define PI 3.1415926535

typedef struct s_coordinate
{
	float	x;
	float	y;
}	t_coordinate;

typedef struct s_ray
{
	t_coordinate	start;
	t_coordinate	dir;
	t_coordinate	unit_step;
	t_coordinate	ray_len_1d;
	int				step_x;
	int				step_y;
	float			ray_len;
	int				hit_axis;
}	t_ray;

typedef struct s_config
{
	int		fd;
	char	*path_to_no;
	char	*path_to_so;
	char	*path_to_we;
	char	*path_to_ea;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	char	*map_tmp;
	t_list	*map_list;
	int		map_size;
	int		map_row;
	char	**map;
}	t_config;

typedef struct s_player
{
	t_coordinate	*coordinate;
	t_coordinate	*t_left;
	t_coordinate	*t_right;
	t_coordinate	*b_left;
	t_coordinate	*b_right;
	float	angle;
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	void		*mini_map_img;
	void		*player_img;
	void		*world_img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_mlx;

typedef struct s_data
{
	t_config	*config;
	t_mlx		*mlx;
	t_player	*player;
	t_ray		*rays;
	int			r_idx;
	int			r_count;
}	t_data;

/* init_config.c */
void		init_config(t_config *config, char *map_path);

/* init_data.c */
void		init_data(t_data *data, t_config *config);
void		init_player_hitbox(t_player *player);

/* parse_config.c */
void		parse_config(t_config *config);

/* parse_config_utils.c */
int			is_empty_line(char *line);
void		set_map_null(t_config *config);
int			trim_empty_lines_after_map(t_config *config);
void		trim_map_first_spaces(t_config *config);
void		trim_map_back_spaces(t_config *config);

/* parse_config_elements.c */
int			parse_element(t_config *config, char *line);

/* parse_config_elements_utils.c*/
int			is_map_content(char *str);
int			count_strs(char **strs);
int			join_strs(char ***strs, char **tmp);

/* parse_config_walls */
int			check_walls(t_config *config);

/* render.c */
void		render(t_config *config);
void 		render_minimap(t_data *data, t_mlx *mlx, t_config *config, t_coordinate* coordinate);

/* put_to_mlx.c */
void		put_square(t_mlx *mlx, float x, float y, int player);
void		put_vectors(t_data *data);
void put_one_vector(t_data *data, float angle, int color);
void		put_pixel(t_mlx *mlx, int x, int y, int color);

/* move.c */
void		move_player(int keycode, t_data *data);

/* event.c */
int			event_move(int keycode, t_mlx* mlx);
int			event_close(t_mlx *mlx);

/* free.c */
void		free_set_null(char **arr);
void		free_config(t_config *config);
void		free_2d_char(char ***arr, int size);
void		free_config_exit_msg(t_config *config, int status, const char* msg);

/* get_structs_address.c */
t_data		*get_data_address(t_data* data);
t_mlx		*get_mlx_address(t_mlx* mlx);
t_config	*get_config_address(t_config* config);

/* render_3d.c */
void	draw_3d_walls(t_data *data);
void	dda(t_data *data);

#endif
