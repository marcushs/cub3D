/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:20:45 by hleung            #+#    #+#             */
/*   Updated: 2023/10/18 10:38:00 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	dda(t_data *data)
{
	// t_ray	ray;
	t_coordinate	start;
	t_coordinate	dir;
	t_coordinate	unit_step;
	t_coordinate	ray_len_1d;
	// t_coordinate	plane;
	int				step_x;
	int				step_y;
	int				hit_axis;
	int	map_x;
	int	map_y;

	start.x = data->player->coordinate->x;
	start.y = data->player->coordinate->y;
	map_x = start.x;
	map_y = start.y;
	dir.x = cos(data->player->angle);
	dir.y = -(sin(data->player->angle));
	// plane.x = 0; // sin(data->player->angle);
	// plane.y = 0.66;
	if (dir.x == 0)
		unit_step.x = 1e30;
	else 
		unit_step.x = sqrtf(1 + powf(dir.y/dir.x, 2));
	if (dir.y == 0)
		unit_step.y = 1e30;
	else
		unit_step.y = sqrtf(1 + powf(dir.x/dir.y, 2));
	if (dir.x < 0)
	{
		step_x = -1;
		ray_len_1d.x = (start.x - (float)map_x) * unit_step.x;
		start.x += dir.x;
	}
	else
	{
		step_x = 1;
		ray_len_1d.x = ((float)(map_x + 1) - start.x) * unit_step.x;
		start.x += dir.x;
	}
	if (dir.y < 0)
	{
		step_y = -1;
		ray_len_1d.y = (start.y - (float)map_y) * unit_step.y;
		start.y += dir.y;
	}
	else
	{
		step_y = 1;
		ray_len_1d.y = ((float)(map_y + 1) - start.y) * unit_step.y;
		start.y += dir.y;
	}
	// float max_len = 8.0;
	int	hit = 0;
	while (!hit && map_x < (data->config->map_row - 1) && map_x >= 0 && map_y < (data->config->map_size - 1) && map_y >= 0)
	{
		if (ray_len_1d.x < ray_len_1d.y)
		{
			map_x += step_x;
			ray_len_1d.x += unit_step.x;
			start.x += dir.x;
			hit_axis = 0;
		}
		else
		{
			map_y += step_y;
			ray_len_1d.y += unit_step.y;
			start.y += dir.y;
			hit_axis = 1;
		}
		if (data->config->map[(int)start.y][(int)start.x] == '1')
		{
			hit = 1;
			put_pixel(data->mlx, (start.x + 1) * 15, (start.y + 1)  * 15, 0x00FF0000);
			return ;
		}
	}
	printf("hit axis %d\n", hit_axis);
	// data->rays[data->r_idx++] = ray;
}
