/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:20:45 by hleung            #+#    #+#             */
/*   Updated: 2023/10/17 17:17:41 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	dda(t_data *data)
{
	t_ray	ray;
	// t_coordinate	intersection;
	int	map_x;
	int	map_y;
	// float	ray_distance;

	ray.start.x = data->player->coordinate->x;
	ray.start.y = data->player->coordinate->y;
	map_x = ray.start.x;
	map_y = ray.start.y;
	ray.dir.x = cos(data->player->angle);
	ray.dir.y = -(sin(data->player->angle));
	printf("dir x %f\n", ray.dir.x);
	printf("dir y %f\n", ray.dir.y);
	if (ray.dir.x == 0)
		ray.unit_step.x = 1e30;
	else 
		ray.unit_step.x = sqrtf(1 + powf(ray.dir.y/ray.dir.x, 2));
	if (ray.dir.y == 0)
		ray.unit_step.y = 1e30;
	else
		ray.unit_step.y = sqrtf(1 + powf(ray.dir.x/ray.dir.y, 2));
	if (ray.dir.x < 0)
	{
		ray.step_x = -1;
		ray.ray_len_1d.x = (ray.start.x - (float)map_x) * ray.unit_step.x;
	}
	else
	{
		ray.step_x = 1;
		ray.ray_len_1d.x = ((float)(map_x + 1) - ray.start.x) * ray.unit_step.x;
	}
	if (ray.dir.y < 0)
	{
		ray.step_y = -1;
		ray.ray_len_1d.y = (ray.start.y - (float)map_y) * ray.unit_step.y;
	}
	else
	{
		ray.step_y = 1;
		ray.ray_len_1d.y = ((float)(map_y + 1) - ray.start.y) * ray.unit_step.y;
	}
	printf("before loop cell is x = %f y = %f char = %c\n", ray.ray_len_1d.x, ray.ray_len_1d.y, data->config->map[map_y][map_x]);
	put_pixel(data->mlx, (map_x + 1) * 15, (map_y + 1)  * 15, 0x00FF0000);
	// float max_len = 8.0;
	int	hit = 0;
	while (!hit && ray.start.x < (data->config->map_row - 1) && ray.start.x >= 0 && ray.start.y < (data->config->map_size - 1) && ray.start.y >= 0)
	{
		if (ray.ray_len_1d.x < ray.ray_len_1d.y)
		{
			printf("ray len 1d x shorter\n");
			map_x += ray.step_x;
			ray.ray_len_1d.x += ray.unit_step.x;
			put_pixel(data->mlx, (map_x + 1) * 15, (map_y + 1)  * 15, 0x00FF0000);
			printf("map x = %d\n", map_x);
			printf("cell is x = %f y = %f char = %c\n", ray.ray_len_1d.x, ray.ray_len_1d.y, data->config->map[map_y][map_x]);
			ray.hit_axis = 0;
		}
		else
		{
			printf("ray len 1d y shorter\n");
			map_y += ray.step_y;
			ray.ray_len_1d.y += ray.unit_step.y;
			put_pixel(data->mlx, (map_x + 1) * 15, (map_y + 1)  * 15, 0x0000FF00);
			printf("map y = %d\n", map_y);
			printf("cell is x = %f y = %f char = %c\n", ray.ray_len_1d.x, ray.ray_len_1d.y, data->config->map[map_y][map_x]);
			ray.hit_axis = 1;
		}
		printf("after step map_x is %d and map_y is %d\n", map_x, map_y);
		// if (ray.dir.x < 0)
		// {
		// 	if (data->config->map[map_y][map_x - 1] == '1')
		// 	{
		// 		hit = 1;
		// 		put_pixel(data->mlx, (map_x) * 15, (map_y + 1)  * 15, 0x00FF0000);
		// 		return ;
		// 	}
		// }
		// if (ray.dir.y < 0)
		// {
		// 	if (data->config->map[map_y - 1][map_x] == '1')
		// 	{
		// 		hit = 1;
		// 		put_pixel(data->mlx, (map_x + 1) * 15, (map_y)  * 15, 0x00FF0000);
		// 		return ;
		// 	}
		// }
		if (data->config->map[map_y][map_x] == '1')
		{
			hit = 1;
			put_pixel(data->mlx, (map_x + 1) * 15, (map_y + 1)  * 15, 0x00FF0000);
			return ;
		}
	}
	data->rays = &ray;
}
