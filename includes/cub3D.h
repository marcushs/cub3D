/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:22:33 by hleung            #+#    #+#             */
/*   Updated: 2023/09/29 23:37:06 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# define INV_ID "Error:\nInvalid identifier!\n"
# define NO_PATH "Error:\nNo path specified!\n"
# define OUT_RANGE "Error:\nValue out of range!\n"
# define MAP_EMPTY "Error:\nEmpty line in map content!\n"
# define MALLOC_ERR "Malloc error!\n"

typedef struct s_config
{
	char	*path_to_NO;
	char	*path_to_SO;
	char	*path_to_WE;
	char	*path_to_EA;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	char	*map_tmp;
	t_list	*map_list;
}	t_config;

void	config_init(t_config *config);
void	parse_config(t_config *config, char *path);
int		is_empty_line(char *line);
void	free_2d_char(char ***arr);
void	free_config(t_config *config);
void	free_set_null(char **arr);

#endif
