/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:29:49 by hleung            #+#    #+#             */
/*   Updated: 2023/10/13 18:44:30 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	init_player(t_player *player, t_coordinate *coordinate);
static void	init_player_position(t_mlx *mlx, t_data *data);

void	config_init(t_config *config, char *map_path)
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
	if (!is_valid_file_extension(map_path))
	{
		printf(INV_EXT);
		exit(EXIT_FAILURE);
	}
	config->fd = open(map_path, O_RDONLY);
	if (config->fd == -1)
	{
		printf("%s file not found\n", map_path);
		exit(EXIT_FAILURE);
	}
}

void	t_mlx_init(t_mlx *mlx, t_player *player, t_coordinate *coordinate)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 2500, 1500, "Cub3D");
	mlx->mini_map_img = NULL;
	mlx->player_img = NULL;
	mlx->addr = NULL;
	init_player(player, coordinate);
	init_player_position(mlx, get_data_address(NULL));
	init_player_hitbox(player);
	return ;
}

static void	init_player(t_player *player, t_coordinate *coordinate)
{
	static t_coordinate	top_left;
	static t_coordinate	top_right;
	static t_coordinate	bottom_left;
	static t_coordinate	bottom_right;

	player->coordinate = coordinate;
	player->t_left = &top_left;
	player->t_right = &top_right;
	player->b_left = &bottom_left;
	player->b_right = &bottom_right;
	return ;
}

void	init_player_hitbox(t_player *player)
{
	player->t_left->x = player->coordinate->x - 0.15;
	player->t_left->y = player->coordinate->y - 0.15;
	player->t_right->x = player->coordinate->x + 0.15;
	player->t_right->y = player->coordinate->y - 0.15;
	player->b_left->x = player->coordinate->x - 0.15;
	player->b_left->y = player->coordinate->y + 0.15;
	player->b_right->x = player->coordinate->x + 0.15;
	player->b_right->y = player->coordinate->y + 0.15;
}

static void	init_player_position(t_mlx *mlx, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	(void)mlx;
	while (y < data->config->map_size && data->config->map[y])
	{
		while (x < (int)ft_strlen(data->config->map[y]) && \
		data->config->map[y][x] && data->config->map[y][x] != '\n')
		{
			if (data->config->map[y][x] == 'N')
			{
				data->player->coordinate->y = (float)y + 0.5;
				data->player->coordinate->x = (float)x + 0.5;
			}
			x++;
		}
		x = 0;
		y++;
	}
	data->player->angle = 0;
}
