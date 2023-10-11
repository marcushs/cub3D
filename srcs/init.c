/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:29:49 by hleung            #+#    #+#             */
/*   Updated: 2023/10/11 17:25:53 by tduprez          ###   ########lyon.fr   */
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
	config->map_row = 0;
	config->map = NULL;
}

// void	data_init(t_data *data)
// {
// 	// data->pi = 3.14;
// 	// data->x_case = 20;
// 	// data->y_case = 15;
// 	// data->block_size = 64;
// 	// data->width_screen = data->x_case * data->block_size;
// 	// data->height_screen = data->y_case * data->block_size;
// 	return ;
// }

void	create_player_position(t_mlx *mlx, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	(void)mlx;
	while (y < data->config->map_size && data->config->map[y])
	{
		while (x < (int)ft_strlen(data->config->map[y]) && data->config->map[y][x] && data->config->map[y][x] != '\n')
		{
			if (data->config->map[y][x] == 'N')
			{
				mlx->player->coordinate->y = (float)y + 0.5;
				mlx->player->coordinate->x = (float)x + 0.5;
			}
			x++;
		}
		x = 0;
		y++;
	}
	mlx->player->angle = 0;
}

void	init_player_hitbox(t_mlx *mlx)
{
	(void)mlx;
	mlx->player->top_left->x = mlx->player->coordinate->x - 0.25;
	mlx->player->top_left->y = mlx->player->coordinate->y - 0.25;
	mlx->player->top_right->x = mlx->player->coordinate->x + 0.25;
	mlx->player->top_right->y = mlx->player->coordinate->y - 0.25;
	mlx->player->bottom_left->x = mlx->player->coordinate->x - 0.25;
	mlx->player->bottom_left->y = mlx->player->coordinate->y + 0.25;
	mlx->player->bottom_right->x = mlx->player->coordinate->x + 0.25;
	mlx->player->bottom_right->y = mlx->player->coordinate->y + 0.25;
}

void	init_player(t_coordinate *top_left, t_coordinate *top_right, t_coordinate *bottom_left, t_coordinate *bottom_right)
{
	get_mlx_address(NULL)->player->top_left = top_left;
	get_mlx_address(NULL)->player->top_right = top_right;
	get_mlx_address(NULL)->player->bottom_left = bottom_left;
	get_mlx_address(NULL)->player->bottom_right = bottom_right;
}

void	t_mlx_init(t_mlx *mlx, t_data *data, t_player *player, t_coordinate *coordinate, t_coordinate *top_left, t_coordinate *top_right, t_coordinate *bottom_left, t_coordinate *bottom_right)
{
	(void)data;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 2500, 1500, "Cub3D");
	mlx->mini_map_img = NULL;
	mlx->player_img = NULL;
	mlx->addr = NULL;
	mlx->player = player;
	mlx->player->coordinate = coordinate;
	init_player(top_left, top_right, bottom_left, bottom_right);
	return ;
}
