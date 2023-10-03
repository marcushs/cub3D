/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:22:33 by hleung            #+#    #+#             */
/*   Updated: 2023/10/03 10:54:37 by hleung           ###   ########.fr       */
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
	char	**map;
}	t_config;

/* init.c */
void	config_init(t_config *config);

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

#endif
