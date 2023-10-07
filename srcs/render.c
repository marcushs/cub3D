/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/06 17:37:12 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	raycasting(t_config *config)
{
	t_data	data;
	t_mlx	mlx;

	get_config_address(config);
	get_data_address(&data);
	get_mlx_address(&mlx);
	(void)config;
	// data_init(&data);
	data.config = config;
	data.mlx = &mlx;
	t_mlx_init(&mlx, &data);
	mlx_hook(mlx.mlx_win, 17, 0, &event_close, &mlx);
	mlx_hook(mlx.mlx_win, 2, (1L<<0), &event_move, &mlx);
	mlx_loop_hook(mlx.mlx, &event_key_hook, &data);
	mlx_loop(mlx.mlx);
}

void	render_minimap(t_data *data)
{
	int	x;
	int	y;
	
	data->config->map_row = map_longest_row(data);
	data->mlx->mini_map_img = mlx_new_image(data->mlx->mlx,(data->config->map_row + 1) * 15, (data->config->map_size + 1) * 15);
	//data->mlx->player_img = mlx_new_image(data->mlx->mlx, 6, 6);
	data->mlx->addr = mlx_get_data_addr(data->mlx->mini_map_img, &data->mlx->bits_per_pixel, &data->mlx->line_length, &data->mlx->endian);
	y = 0;
	while (y < data->config->map_size)
	{
		x = 0;
		while (data->config->map[y][x] && data->config->map[y][x] != '\n')
		{
			if (data->config->map[y][x] == '1')
				put_square(data->mlx, x, y, 0);
			if (data->config->map[y][x] == 'N')
				put_square(data->mlx, x, y, 1);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->mini_map_img, 0, 0);
	//mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->player_img, 0, 0);
	mlx_destroy_image(data->mlx->mlx, data->mlx->mini_map_img);
	//mlx_destroy_image(data->mlx->mlx, data->mlx->player_img);
}

void	put_square(t_mlx *mlx, int x, int y, int player)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = (x + 1) * 15 +  (player * 5);
	start_y = (y + 1) * 15 + (player * 5);
	end_x = start_x + 14 + (player * -8);
	end_y = start_y + 14 + (player * -8);
	while (start_y < end_y)
	{
		while (start_x < end_x)
		{
			if (player)
				my_mlx_pixel_put(mlx, start_x, start_y, 0x00FF0000);
			else
				my_mlx_pixel_put(mlx, start_x, start_y, 0x00999999);
			start_x++;
		}
		start_x -= 14 - (player * 8);
		start_y++;
	}
}

// void	put_player(t_mlx *mlx, int x, int y)
// {
// 	while (start_y < end_y)
// 	{
// 		while (start_x < end_x)
// 		{
// 			my_mlx_pixel_put(mlx, start_x, start_y, 0x00FF0000);
// 			start_x++;
// 		}
// 		start_x -= 6;
// 		start_y++;
// 	}
// 	mlx->player->x = start_x;
// 	mlx->player->y = start_y;
// }


void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	map_longest_row(t_data *data)
{
	int	max;
	int	len;
	int	y;

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
