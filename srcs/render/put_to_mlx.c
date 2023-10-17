/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:25:36 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/17 16:08:26 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void put_one_vector(t_data *data, float angle, int color);
void put_pixel(t_mlx *mlx, int x, int y, int color);
void	set_rays_dist(t_data *data, float vx, float vy);

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
	data->r_count = 0;
	while (i < range)
	{
		i += 0.05;
		data->r_count++;
	}
	data->rays = (t_ray *)malloc(sizeof(t_ray) * data->r_count); //need protection
	i = -range;
	while (i < range)
	{
		put_one_vector(data, data->player->angle + i, 0x00FF0000);
		i += 0.05;
	}
	put_one_vector(data, data->player->angle, 0x00FF00);
}

void put_one_vector(t_data *data, float angle, int color)
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
	// if (color == 0x00FF0000)
	// 	set_rays_dist(data, vector_x, vector_y);
	// float lineH = (15 * 15 * 950)/ray_dis; if (lineH > 950){lineH = 950;}
	return;
}

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return;
}

// void	set_rays_dist(t_data *data, float vx, float vy)
// {
// 	static t_ray	ray;
	
// 	printf("vx is %f\n", vx);
// 	printf("vy is %f\n", vy);
// 	printf("players x %f\n", data->player->coordinate->x);
// 	printf("players y %f\n", data->player->coordinate->y);
// 	ray.dis_x = fabsf(vx - data->player->coordinate->x);
// 	ray.dis_y = fabsf(vy - data->player->coordinate->x);
// 	ray.ray_len = sqrtf(powf(ray.dis_x, 2) + powf(ray.dis_y, 2));
// 	data->rays[data->r_idx] = ray;
// 	data->r_idx++;
// 	if (data->r_idx == data->r_count)
// 		data->r_idx = 0;
// }
