/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:25:36 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/14 13:33:39 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void put_one_vector(t_data *data, float angle, int color);
static void put_pixel(t_mlx *mlx, int x, int y, int color);

void put_square(t_mlx *mlx, float x, float y, int player)
{
	float start_x;
	float start_y;
	float end_x;
	float end_y;

	start_x = (x + 1) * 15 + ((player * -0.20) * 15);
	start_y = (y + 1) * 15 + ((player * -0.20) * 15);
	end_x = start_x + 14 + (player * -7);
	end_y = start_y + 14 + (player * -7);
	while (start_y < end_y)
	{
		while (start_x < end_x)
		{
			if (player)
				put_pixel(mlx, start_x, start_y, 0x00FF0000);
			else
				put_pixel(mlx, start_x, start_y, 0x00999999);
			start_x++;
		}
		start_x -= 14 - (player * 7);
		start_y++;
	}
}

void put_vectors(t_data *data)
{
	float range;
	float i;

	range = (30.0 / 180.0) * PI;
	i = -range;
	while (i < range)
	{
		put_one_vector(data, data->player->angle + i, 0x00FF0000);
		i += 0.05;
	}
	put_one_vector(data, data->player->angle, 0x00FF00);
}

static void put_one_vector(t_data *data, float angle, int color)
{
	float vector_x = data->player->coordinate->x;
	float vector_y = data->player->coordinate->y;
	float step_size = 0.01;
	float len = 0.00;

	while (data->config->map[(int)vector_y] && data->config->map[(int)vector_y][(int)vector_x] != '1' && len < 8.0)
	{
		put_pixel(data->mlx, (vector_x + 1) * 15, (vector_y + 1) * 15, color);
		vector_x += cos(angle) * step_size;
		vector_y -= sin(angle) * step_size;
		len += step_size;
	}
	return;
}

static void put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return;
}
