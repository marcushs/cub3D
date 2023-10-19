/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:51:27 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/19 23:33:39 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_t_mlx(t_mlx *mlx);
static void	init_player(t_player *player, t_coordinate *coordinate);
static void	init_player_position(t_data *data);

void	init_data(t_data *data, t_config *config)
{
	static t_mlx		mlx;
	static t_player		player;
	static t_coordinate	coordinate;

	get_mlx_address(&mlx); 
	data->config = config;
	data->mlx = &mlx;
	data->player = &player;
	data->rays = NULL;
	data->r_idx = 0;
	data->r_count = 0;
	init_t_mlx(&mlx);
	init_player(&player, &coordinate);
	init_player_position(data);
	init_player_hitbox(&player);
	return ;
}

void	init_img(t_image *img, int width, int height)
{
	img->img = NULL;
	img->img_addr = NULL;
	img->width = width;
	img->height = height;
	return ;
}

static void	init_t_mlx(t_mlx *mlx)
{
	static t_image	mini_map;
	static t_image	player;
	static t_image	window;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 2500, 1500, "Cub3D");
	mlx->mini_map_img = NULL;
	mlx->player_img = NULL;
	mlx->addr = NULL;
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

static void	init_player_position(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->config->map_size && data->config->map[y])
	{
		while (x < (int)ft_strlen(data->config->map[y]) && \
		data->config->map[y][x] && data->config->map[y][x] != '\n')
		{
			if (data->config->map[y][x] == 'N' || data->config->map[y][x] == 'W' || data->config->map[y][x] == 'S' || data->config->map[y][x] == 'E')
			{
				if (data->config->map[y][x] == 'N')
					data->player->angle = -M_PI_2;
				else if (data->config->map[y][x] == 'E')
					data->player->angle = M_PI;
				else if (data->config->map[y][x] == 'S')
					data->player->angle = M_PI_2;
				else
					data->player->angle = 0;
				data->player->coordinate->y = (float)y + 0.5;
				data->player->coordinate->x = (float)x + 0.5;
			}
			x++;
		}
		x = 0;
		y++;
	}
	// data->player->angle = 0;
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
	return ;
}
