/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:22:33 by hleung            #+#    #+#             */
/*   Updated: 2023/09/21 14:46:34 by hleung           ###   ########.fr       */
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

typedef struct s_map
{
	char	*path_to_NO;
	char	*path_to_SO;
	char	*path_to_WE;
	char	*path_to_EA;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}	t_map;

int	parse_map(t_map *map, char *path);

#endif
