/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:51:27 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/14 12:27:36 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_t_mlx(t_mlx *mlx, t_config *config);
static void	init_vision(t_data *data);
static void	init_keyboard(t_data *data);

void	init_data(t_data *data, char *map_path)
{
	t_config	config;
	t_mlx		mlx;
	t_player	player;

	init_config(&config, map_path);
	data->config = config;
	data->cell_size = 40;
	data->h_size = data->cell_size * data->config.map_size;
	init_t_mlx(&mlx, &config);
	data->mlx = mlx;
	init_player(&player);
	data->player = player;
	init_player_position(data);
	init_player_dir(data);
	data->move_speed = 3;
	data->rot_speed = 0.05;
	init_vision(data);
	init_keyboard(data);
	init_text(data);
	init_image_data(&data->mlx, &data->config, data);
	data->w_size = data->cell_size * data->config.map_row;
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

static void	init_t_mlx(t_mlx *mlx, t_config *config)
{
	static t_image	mini_map;
	static t_image	player;
	static t_image	window;
	static t_image	mmb;

	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		free_config_exit_msg(config, EXIT_FAILURE, MLX_ERR);
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "Cub3D");
	if (!mlx->mlx_win)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		free_config_exit_msg(config, EXIT_FAILURE, MLX_ERR);
	}
	mlx->mini_map = &mini_map;
	mlx->player = &player;
	mlx->window = &window;
	mlx->mmb = &mmb;
	init_img(mlx->mini_map, 0, 0);
	init_img(mlx->player, PLAYER_W, PLAYER_H);
	init_img(mlx->mmb, MAP_W, MAP_H);
	init_img(mlx->window, WIN_W, WIN_H);
	return ;
}

static void	init_vision(t_data *data)
{
	data->fov = 100;
	data->view_dst = 800;
	data->ray_nb = WIN_W * 0.5;
	data->rays = (t_ray *)malloc(sizeof(t_ray) * data->ray_nb);
	if (!data->rays)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
		mlx_destroy_display(data->mlx.mlx);
		free_data(data);
		exit(EXIT_FAILURE);
	}
}

static void	init_keyboard(t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
		data->keyboard[i++] = 0;
}
