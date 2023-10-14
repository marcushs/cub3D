/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/14 13:45:26 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int map_longest_row(t_data *data);

void render(t_config *config)
{
	t_data data;

	get_data_address(&data);
	init_data(&data, config);
	mlx_hook(data.mlx->mlx_win, 17, 0, &event_close, data.mlx);
	mlx_hook(data.mlx->mlx_win, 2, (1L << 0), &event_move, data.mlx);
	render_minimap(&data, data.mlx, data.config, data.player->coordinate);
	mlx_loop(data.mlx->mlx);
	return;
}

void render_minimap(t_data *data, t_mlx *mlx, t_config *config, t_coordinate* coordinate)
{
	int x;
	int y;

	config->map_row = map_longest_row(data);
	mlx->mini_map_img = mlx_new_image(mlx->mlx, (config->map_row + 1) * 15, (config->map_size + 1) * 15);
	mlx->addr = mlx_get_data_addr(mlx->mini_map_img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	y = 0;
	while (y < config->map_size)
	{
		x = 0;
		while (config->map[y][x] && config->map[y][x] != '\n')
		{
			if ((int)coordinate->y == y && (int)coordinate->x == x)
				put_square(mlx, coordinate->x, coordinate->y, 1);
			else if (config->map[y][x] == '1')
				put_square(mlx, x, y, 0);
			x++;
		}
		y++;
	}
	put_vectors(data);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->mini_map_img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->mini_map_img);
	return;
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
