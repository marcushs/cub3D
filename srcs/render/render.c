/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/26 22:27:57 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	render(t_config *config)
{
	t_data data;

	get_data_address(&data);
	init_data(&data, config);
	mlx_hook(data.mlx->mlx_win, 17, 0, &event_close, data.mlx);
	mlx_hook(data.mlx->mlx_win, 2, (1L << 0), &event_move, data.mlx);
	init_image_data(data.mlx, config);
	render_minimap(&data);
	render_player(data.mlx->player);
	dda(&data);
	put_window_image_to_window(data.mlx, data.player->coordinate->x, \
	data.player->coordinate->y);
	mlx_loop(data.mlx->mlx);
	return;
}

void	render_border(t_data *data);

void	put_window_image_to_window(t_mlx *m, float x, float y)
{
	(void)y;
	(void)x;
	ft_put_img_to_img(m->mini_map_border, m->mini_map, 0, 0);
	render_border(get_data_address(NULL));
	ft_put_img_to_img(m->mini_map_border, m->player, 10, 10);
	ft_put_img_to_img(m->window, m->mini_map_border, 30, 30);
	mlx_put_image_to_window(m->mlx, m->mlx_win, m->window->img, 0, 0);
	return ;
}

void	render_border(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (x < 2 || y < 2 || y > MAP_HEIGHT - 2 || x > MAP_WIDTH - 2)
				put_pixel(data->mlx->mini_map_border, x, y, 0x8395a7);
			x++;
		}
		y++;
	}
	return ;
}


void render_minimap(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->config->map_size)
	{
		x = 0;
		while (data->config->map[y][x] && data->config->map[y][x] != '\n')
		{
			if (data->config->map[y][x] == '1')
				put_square(data->mlx, x, y, 0);
			x++;
		}
		y++;
	}
	render_border(data);
	return;
}

void render_player(t_image *player)
{
	int	x;
	int	y;

	y = 0;

	while (y < 8)
	{
		x = 0;
		while (x < 8)
			put_pixel(player, x++, y, 0x00FF0000);
		y++;
	}
	return ;
}
