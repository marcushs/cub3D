/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:51:27 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/08 15:35:30 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_t_mlx(t_mlx *mlx);
static void	init_player(t_player *player);
static void	init_player_position(t_data *data);
static void	init_vision(t_data *data);
static void	init_keyboard(t_data *data);

void	init_data(t_data *data, char *map_path)
{
	t_config	config;
	t_mlx		mlx;
	t_player	player;

	init_config(&config, map_path);
	data->config = config;
	init_t_mlx(&mlx);
	data->mlx = mlx;
	data->cell_size = 15;
	init_player(&player);
	data->player = player;
	init_player_position(data);
	data->move_speed = 3;
	data->rot_speed = 0.05;
	init_vision(data);
	init_keyboard(data);
	init_text(data);
	init_image_data(&data->mlx, &data->config);
	// init_keyboard(data);
	// get_mlx_address(&mlx); 
	// if (!data->config)
	// 	return ;
	// data->rays = NULL;
	// init_player_hitbox(&player);
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
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "Cub3D");
	mlx->mini_map = &mini_map;
	mlx->player = &player;
	mlx->window = &window;
	mlx->mini_map_border = &mini_map_border;
	init_img(mlx->mini_map, 0, 0);
	init_img(mlx->player, PLAYER_W, PLAYER_H);
	init_img(mlx->mini_map_border, MAP_W, MAP_H);
	init_img(mlx->window, WIN_W, WIN_H);
	return ;
}

static void	init_player(t_player *player)
{
	// static t_coor_f		top_left;
	// static t_coor_f		top_right;
	// static t_coor_f		bottom_left;
	// static t_coor_f		bottom_right;

	player->coordinate.x = 0;
	player->coordinate.y = 0;
	player->dir.x = 0;
	player->dir.y = 0;
	player->view_dst_pos.x = 0;
	player->view_dst_pos.y = 0;
	player->angle = 0;
	player->ori = 0;
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
	char	**map;

	x = 0;
	y = 0;
	map = data->config.map;
	while (y < data->config.map_size && map[y])
	{
		while (x < (int)ft_strlen(map[y]) && map[y][x] && map[y][x] != '\n')
		{
			if (map[y][x] == N || map[y][x] == W || map[y][x] == S || map[y][x] == E)
			{
				data->player.ori = map[y][x];
				data->player.coordinate.y = (float)y + 0.5;
				data->player.coordinate.x = (float)x + 0.5;
			}
			x++;
		}
		x = 0;
		y++;
	}
	return ;
}

// void	init_player_hitbox(t_player *player)
// {
// 	player->t_left.x = player->coordinate->x - 0.15;
// 	player->t_left.y = player->coordinate->y - 0.15;
// 	player->t_right.x = player->coordinate->x + 0.15;
// 	player->t_right.y = player->coordinate->y - 0.15;
// 	player->b_left.x = player->coordinate->x - 0.15;
// 	player->b_left.y = player->coordinate->y + 0.15;
// 	player->b_right.x = player->coordinate->x + 0.15;
// 	player->b_right.y = player->coordinate->y + 0.15;
// 	return ;
// }

static void	init_vision(t_data *data)
{
	data->fov = 66;
	data->view_dst = 800;
	data->ray_nb = WIN_W * 0.5;
	data->rays = (t_ray *)malloc(sizeof(t_ray) * data->ray_nb);
	if (!data->rays)
		free_config_exit_msg(&data->config, EXIT_FAILURE, MALLOC_ERR);
}

static void	init_keyboard(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < 200)
		data->keyboard[i] = 0;
}
