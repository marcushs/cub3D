/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/19 23:34:09 by tduprez          ###   ########lyon.fr   */
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
	put_window_image_to_window(data.mlx, data.player->coordinate->x, \
	data.player->coordinate->y);
	mlx_loop(data.mlx->mlx);
	return;
}

void	put_window_image_to_window(t_mlx *m, float x, float y)
{
	ft_put_img_to_img(m->window, m->mini_map, 0, 0);
	ft_put_img_to_img(m->window, m->player, (x + 1) * 15 - 4, (y + 1) * 15 - 4);
	mlx_put_image_to_window(m->mlx, m->mlx_win, m->window->img, 0, 0);
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
<<<<<<< HEAD
=======
	put_one_vector(data, data->player->angle, 0x00FF00);
	dda(data);
	// printf("player->coordinate->x %f\n", data->player->coordinate->x);
	// printf("player->coordinate->y %f\n", data->player->coordinate->y);
	//put_vectors(data);
	// for (int i = 0; i < data->r_count; i++)
	// {
	// 	// printf("data->rays[%d]->dis_x = %f\n", i, data->rays[i].dis_x);
	// 	printf("data->rays[%d]->dis_y = %f\n", i, data->rays[i].dis_y);
	
	// }
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->mini_map_img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->mini_map_img);
>>>>>>> marcus_raycast
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
