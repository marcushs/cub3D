/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/13 11:58:30 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_direction_vector(t_data *data);
float	get_len_direction_vector(t_data *data);

void	raycasting(t_config *config)
{
	t_data			data;
	t_mlx			mlx;
	t_player		player;
	t_coordinate	coordinate;;

	get_config_address(config);
	get_data_address(&data);
	get_mlx_address(&mlx);
	(void)config;
	data.config = config;
	data.mlx = &mlx;
	data.player = &player;
	t_mlx_init(&data, &player, &coordinate);
	create_player_position(&mlx, &data);
	init_player_hitbox(&player);
	mlx_hook(mlx.mlx_win, 17, 0, &event_close, &mlx);
	mlx_hook(mlx.mlx_win, 2, (1L<<0), &event_move, &mlx);
	render_minimap(&data);
	mlx_loop_hook(mlx.mlx, &event_key_hook, &data);
	mlx_loop(mlx.mlx);
}

void	put_vector(t_data *data, float angle)
{
	float vector_x = data->player->coordinate->x;
	float vector_y = data->player->coordinate->y;
	float step_size = 0.01;
	float len = 0.00;

	while (data->config->map[(int)vector_y] && data->config->map[(int)vector_y][(int)vector_x] != '1' && len < 8.0)
	{
		my_mlx_pixel_put(data->mlx, (vector_x + 1) * 15, (vector_y + 1) * 15, 0x00FF0000);
		vector_x += cos(angle) * step_size;
		vector_y -= sin(angle) * step_size;
		len += step_size;
	}
}

void	render_minimap(t_data *data)
{
	int	x;
	int	y;

	data->config->map_row = map_longest_row(data);
	data->mlx->mini_map_img = mlx_new_image(data->mlx->mlx,(data->config->map_row + 1) * 15, (data->config->map_size + 1) * 15);
	data->mlx->addr = mlx_get_data_addr(data->mlx->mini_map_img, &data->mlx->bits_per_pixel, &data->mlx->line_length, &data->mlx->endian);
	y = 0;
	while (y < data->config->map_size)
	{
		x = 0;
		while (data->config->map[y][x] && data->config->map[y][x] != '\n')
		{
			if ((int)data->player->coordinate->y == y && (int)data->player->coordinate->x == x)
				put_square(data->mlx, data->player->coordinate->x, data->player->coordinate->y, 1);
			else if (data->config->map[y][x] == '1')
				put_square(data->mlx, x, y, 0);
			x++;
		}
		y++;
	}
	float test = (30.0 / 180.0) * PI;
	printf("%f\n", test);
	for (float i = -test; i < test; i += 0.05)
		put_vector(data, data->player->angle + i);
	put_direction_vector(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->mini_map_img, 0, 0);
	mlx_destroy_image(data->mlx->mlx, data->mlx->mini_map_img);
}

void	put_direction_vector(t_data *data)
{
	float vector_x = data->player->coordinate->x;
	float vector_y = data->player->coordinate->y;
	float step_size = 0.01;
	float len = 0.00;

	while (data->config->map[(int)vector_y] && data->config->map[(int)vector_y][(int)vector_x] != '1' && len < 8.0)
	{
		my_mlx_pixel_put(data->mlx, (vector_x + 1) * 15, (vector_y + 1) * 15, 0x00FF00);
		vector_x += cos(data->player->angle) * step_size;
		vector_y -= sin(data->player->angle) * step_size;
		len += step_size;
	}
}


// float get_len_direction_vector(t_data *data)
// {
// float vector_x = data->player->coordinate->x;
// float vector_y = data->player->coordinate->y;
// float step_size = 0.01;
// float len = 0.0;

// while (data->config->map[(int)vector_y] && data->config->map[(int)vector_y][(int)vector_x] != '1')
// {
// 	vector_x += cos(data->player->angle) * step_size;
// 	vector_y -= sin(data->player->angle) * step_size;
// 	len += step_size;
// }

// return len;
// }




// float	get_len_direction_vector(t_data *data)
// {
// 	float vector_x = data->player->coordinate->x;
// 	float vector_y = data->player->coordinate->y;
// 	float step_size = 0.01;
// 	float	len = 0.00;

// 	while (data->config->map[(int)vector_y] && data->config->map[(int)vector_y][(int)vector_x] != '1')
// 	{
// 		vector_x += cos(data->player->angle) * step_size;
// 		vector_y -= sin(data->player->angle) * step_size;
// 		len+=0.01;
// 	}
// 	return (len);
// }

void	put_square(t_mlx *mlx, float x, float y, int player)
{
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;

	start_x = (x + 1) * 15 + ((player * -0.20) * 15);
	start_y = (y + 1) * 15 + ((player * -0.20) * 15);
	end_x = start_x + 14 + (player * -7);
	end_y = start_y + 14 + (player * -7);
	while (start_y < end_y)
	{
		while (start_x < end_x)
		{
			if (player)
				my_mlx_pixel_put(mlx, start_x , start_y, 0x00FF0000);
			else
				my_mlx_pixel_put(mlx, start_x, start_y, 0x00999999);
			start_x++;
		}
		start_x -= 14 - (player * 7);
		start_y++;
	}
}

// void	put_square(t_mlx *mlx, float x, float y, int player)
// {
// 	float	start_x;
// 	float	start_y;
// 	float	end_x;
// 	float	end_y;

// 	start_x = (x + 1) * 15 + (player * -3);
// 	start_y = (y + 1) * 15 + (player * -3);
// 	end_x = start_x + 14 + (player * -8);
// 	end_y = start_y + 14 + (player * -8);
// 	while (start_y < end_y)
// 	{
// 		while (start_x < end_x)
// 		{
// 			if (player)
// 				my_mlx_pixel_put(mlx, start_x , start_y, 0x00FF0000);
// 			else
// 				my_mlx_pixel_put(mlx, start_x, start_y, 0x00999999);
// 			start_x++;
// 		}
// 		start_x -= 14 - (player * 8);
// 		start_y++;
// 	}
// }

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
// 	player->x = start_x;
// 	player->y = start_y;
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
