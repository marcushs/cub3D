/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:29:49 by hleung            #+#    #+#             */
/*   Updated: 2023/10/05 16:17:06 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	config_init(t_config *config)
{
	config->fd = -1;
	config->path_to_no = NULL;
	config->path_to_so = NULL;
	config->path_to_we = NULL;
	config->path_to_ea = NULL;
	config->map_tmp = NULL;
	config->map_list = NULL;
	config->map_size = 0;
	config->map = NULL;
}

void	data_init(t_data *data)
{
	data->pi = 3.14;
	data->x_case = 20;
	data->y_case = 15;
	data->block_size = 64;
	data->width_screen = 1920;
	data->height_screen = 1920;
	return ;
}

void	t_mlx_init(t_mlx *mlx, t_data *data)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, data->width_screen, data->height_screen, "Cub3D");
	mlx->img = NULL;
	return ;
}
