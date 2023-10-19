/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:20:45 by hleung            #+#    #+#             */
/*   Updated: 2023/10/16 21:32:31 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	dda(t_data *data)
{
	t_ray	ray;

	ray.start.x = data->player->coordinate->x;
	ray.start.y = data->player->coordinate->y;
	ray.dir.x = cos(data->player->angle);
	ray.dir.y = sin(data->player->angle);
	printf("dir_x %f\n", ray.dir.x);
	printf("dir_y %f\n", ray.dir.y);
	ray.unit_step.x = sqrtf(1 * powf(ray.dir.y/ray.dir.x, 2));
	ray.unit_step.y = sqrtf(1 * powf(ray.dir.x/ray.dir.y, 2));
	// printf("scaling factor x %f\n", ray.unit_step.x);
	// printf("scaling factor y %f\n", ray.unit_step.y);
	// printf("dda int player x is %d\n", (int)data->player->coordinate->x);
	// printf("dda int player y is %d\n", (int)data->player->coordinate->y);
	// printf("dda float player x is %f\n", data->player->coordinate->x);
	// printf("dda float player y is %f\n", data->player->coordinate->y);
	if (ray.dir.x < 0)
	{
		ray.step_x = -1;
		ray.ray_len_1d.x = (data->player->coordinate->x - (int)data->player->coordinate->x) * ray.step_x;
		// printf("ray_len_1d.x %f\n", ray.ray_len_1d.x);
	}
	else
	{
		ray.step_x = 1;
		ray.ray_len_1d.x = (((int)data->player->coordinate->x + 1) - data->player->coordinate->x) * ray.step_x;
		// printf("ray_len_1d.x %f\n", ray.ray_len_1d.x);
	}
	if (ray.dir.y < 0)
	{
		ray.step_y = -1;
		ray.ray_len_1d.y = (data->player->coordinate->y - (int)data->player->coordinate->y) * ray.step_y;
		// printf("ray_len_1d.y %f\n", ray.ray_len_1d.y);
	}
	else
	{
		ray.step_y = 1;
		ray.ray_len_1d.y = (((int)data->player->coordinate->y + 1) - data->player->coordinate->y) * ray.step_y;
		// printf("ray_len_1d.y %f\n", ray.ray_len_1d.y);
	}
	float max_len = 8.0;
	while (ray.start.x < data->config->map_row && ray.start.y < data->config->map_size && data->config->map[(int)ray.start.y][(int)ray.start.x] != '1' && ray.ray_len < max_len)
	{
		if (ray.ray_len_1d.x < ray.ray_len_1d.y)
		{
			ray.start.x += ray.step_x;
			ray.ray_len = ray.ray_len_1d.x;
			ray.ray_len_1d.x += ray.unit_step.x;
		}
		else
		{
			ray.start.y += ray.step_y;
			ray.ray_len = ray.ray_len_1d.y;
			ray.ray_len_1d.y += ray.unit_step.y;
		}
	}
	data->rays = &ray;
}
