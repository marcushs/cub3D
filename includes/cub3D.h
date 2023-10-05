/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:22:33 by hleung            #+#    #+#             */
/*   Updated: 2023/10/05 17:22:56 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
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


typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*mini_map;
	void	*player;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_data
{
	t_config	*config;
	t_mlx		*mlx;
	// unsigned int	x_case;
	// unsigned int	y_case;
	// unsigned int	block_size;
	// unsigned int	width_screen;
	// unsigned int	height_screen;
}	t_data;

/* init.c */
void	config_init(t_config *config);
void	data_init(t_data *data);
void	t_mlx_init(t_mlx *mlx, t_data *data);

/* parse_config.c */
void	parse_config(t_config *config, char *path);

/* parse_elements.c */
int		parse_element(t_config *config, char *line);

/* parse_map.c */
void	parse_map(t_config *config);

/* parse_utils.c*/
int		is_empty_line(char *line);
int		is_map_content(char *str);
int		count_strs(char **strs);
int		join_strs(char ***strs, char **tmp);

/* check_map.c */
int		trim_empty_lines_after_map(t_config *config);
int		check_map_chars(t_config *config);
void	check_map_walls(t_config *config);

/* free.c */
void	free_set_null(char **arr);
void	free_config(t_config *config);
void	free_2d_char(char ***arr, int size);
void	free_config_exit_msg(t_config *config, int status, const char* msg);

/* get_structs_address.c */
t_data	*	get_data_address(t_data* data);
t_mlx		*get_mlx_address(t_mlx* mlx);
t_config	*get_config_address(t_config* config);

/* event.c */
int	event_key_hook(int keycode, t_data *data);
int	event_move(int keycode, t_mlx* mlx);
int	event_close(t_mlx *mlx);

/* raycasting.c */
void	raycasting(t_config *config);

#endif
