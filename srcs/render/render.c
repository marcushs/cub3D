/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/19 14:51:29 by tduprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int map_longest_row(t_data *data);
static void put_player_pixel(t_mlx *mlx, int x, int y, int color);
static void put_map_pixel(t_mlx *mlx, int x, int y, int color);

void	ft_put_image_to_image(t_data *data)
{
	printf("%f | %f\n", data->player->coordinate->y, data->player->coordinate->x);
	printf("%d | %d\n", data->config->map_size, data->config->map_row);
	for (int i = 0; i < data->mlx->line_length; i++)
	{
		printf("TEST\n");
		data->mlx->window_addr[i] = data->mlx->mini_map_addr[i];
	}

	for (int y = 0; y < (data->config->map_size + 1) * 15; y++)
	{
		for (int x = 0; x < (data->config->map_row + 1) * 15; x++)
		{
			if ((y >= data->player->coordinate->y * 15 && y <= data->player->coordinate->y * 15 + 8) && (x >= data->player->coordinate->x * 15 && x <= data->player->coordinate->x * 15 + 8))
				put_map_pixel(data->mlx, x, y , 0x00FF0000);
			// else
				// put_map_pixel(data->mlx, x, y, data->mlx->mini_map_addr);
		}
	}
	return ;
}

void render(t_config *config)
{
	t_data data;

	get_data_address(&data);
	init_data(&data, config);
	data.mlx->window_img = mlx_new_image(data.mlx->mlx, (config->map_row + 1) * 15, (config->map_size + 1) * 15);
	mlx_hook(data.mlx->mlx_win, 17, 0, &event_close, data.mlx);
	mlx_hook(data.mlx->mlx_win, 2, (1L << 0), &event_move, data.mlx);
	render_minimap(&data, data.mlx, data.config);
	ft_put_image_to_image(&data);
	mlx_put_image_to_window(data.mlx->mlx, data.mlx->mlx_win, data.mlx->window_img, 0, 0);
	// render_player(&data, data.mlx, data.config, data.player->coordinate);
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
	mlx->window_img = mlx_new_image(mlx->mlx, \
	(config->map_row + 1) * 15, (config->map_size + 1) * 15);
	mlx->window_addr = mlx_get_data_addr(mlx->window_img, \
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
	ft_strlcpy(mlx->window_addr, mlx->mini_map_addr, ft_strlen(mlx->window_addr));
	// mlx->window_addr = ft_strdup(mlx->mini_map_addr);
	return;
}

void render_player(t_data *data, t_mlx *mlx, t_config *config, t_coordinate* c)
{
	int	x;
	int	y;

	y = 0;
	(void)c;
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
	ft_put_image_to_image(data);
	// mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->mini_map_img, 0, 0);
	// mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->player_img, 
	// (c->x + 0.75) * 15, (c->y + 0.75) * 15);
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

static void put_map_pixel(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->window_addr + (y * mlx->line_length + x * \
	(mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return ;
}

