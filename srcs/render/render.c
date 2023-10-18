/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/18 17:29:05 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int map_longest_row(t_data *data);
static void put_player_pixel(t_mlx *mlx, int x, int y, int color);

void render(t_config *config)
{
	t_data data;

	get_data_address(&data);
	init_data(&data, config);
	mlx_hook(data.mlx->mlx_win, 17, 0, &event_close, data.mlx);
	mlx_hook(data.mlx->mlx_win, 2, (1L << 0), &event_move, data.mlx);
	render_minimap(&data, data.mlx, data.config);
	render_player(&data, data.mlx, data.config, data.player->coordinate);
	mlx_loop(data.mlx->mlx);
	return;
}

void render_minimap(t_data *data, t_mlx *mlx, t_config *config)
{
	int x;
	int y;

	config->map_row = map_longest_row(data);
	mlx->mini_map_img = mlx_new_image(mlx->mlx, \
	(config->map_row + 1) * 15, (config->map_size + 1) * 15);
	mlx->mini_map_addr = mlx_get_data_addr(mlx->mini_map_img, \
	&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	y = 0;
	while (y < config->map_size)
	{
		x = 0;
		while (config->map[y][x] && config->map[y][x] != '\n')
		{
			if (config->map[y][x] == '1')
				put_square(mlx, x, y, 0);
			x++;
		}
		y++;
	}
	return;
}

void render_player(t_data *data, t_mlx *mlx, t_config *config, t_coordinate* c)
{
	int	x;
	int	y;

	y = 0;
	config->map_row = map_longest_row(data);
	mlx->player_img = mlx_new_image(mlx->mlx, 8, 8);
	mlx->player_addr = mlx_get_data_addr(mlx->player_img, \
	&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{
			put_player_pixel(mlx, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->mini_map_img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->player_img, \
	(c->x + 0.75) * 15, (c->y + 0.75) * 15);
	mlx_destroy_image(mlx->mlx, mlx->player_img);
	return ;
}

static int map_longest_row(t_data *data)
{
	int max;
	int len;
	int y;

	max = 0;
	y = -1;
	while (++y < data->config->map_size)
	{
		len = 0;
		while (data->config->map[y][len] && data->config->map[y][len] != '\n')
			len++;
		if (len > max)
			max = len;
	}
	return (max);
}

static void put_player_pixel(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->player_addr + (y * mlx->line_length + x * \
	(mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return ;
}
