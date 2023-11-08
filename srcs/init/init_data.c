/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:51:27 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/03 09:14:53 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_t_mlx(t_mlx *mlx);
static void	init_player(t_player *player, t_coor_f *coordinate);
static void	init_player_position(t_data *data);

void	init_data(t_data *data, char *map_path)
{
	static t_mlx		mlx;
	static t_player		player;
	static t_coor_f		coordinate;

	get_mlx_address(&mlx); 
	init_config(data, map_path);
	if (!data->config)
		return ;
	data->mlx = &mlx;
	data->player = &player;
	data->rays = NULL;
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
	static t_image	mini_map_border;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	mlx->mini_map = &mini_map;
	mlx->player = &player;
	mlx->window = &window;
	mlx->mini_map_border = &mini_map_border;
	init_img(mlx->mini_map, 0, 0);
	init_img(mlx->player, PLAYER_WIDTH, PLAYER_HEIGHT);
	init_img(mlx->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	init_img(mlx->mini_map_border, MAP_WIDTH, MAP_HEIGHT);
	return ;
}

static void	init_player(t_player *player, t_coor_f	 *coordinate)
{
	// static t_coor_f		top_left;
	// static t_coor_f		top_right;
	// static t_coor_f		bottom_left;
	// static t_coor_f		bottom_right;

	player->coordinate = coordinate;
	// player->t_left = &top_left;
	// player->t_right = &top_right;
	// player->b_left = &bottom_left;
	// player->b_right = &bottom_right;
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
	player->t_left.x = player->coordinate->x - 0.15;
	player->t_left.y = player->coordinate->y - 0.15;
	player->t_right.x = player->coordinate->x + 0.15;
	player->t_right.y = player->coordinate->y - 0.15;
	player->b_left.x = player->coordinate->x - 0.15;
	player->b_left.y = player->coordinate->y + 0.15;
	player->b_right.x = player->coordinate->x + 0.15;
	player->b_right.y = player->coordinate->y + 0.15;
	return ;
}
