/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:20:45 by hleung            #+#    #+#             */
/*   Updated: 2023/10/16 16:51:20 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	dda(t_data *data)
{
	t_ray	ray;

	ray.start_x = data->player->coordinate->x;
	ray.start_y = data->player->coordinate->y;
	ray.dir_x = cos(data->player->angle);
	ray.dir_y = sin(data->player->angle);
	printf("dir_x %f\n", ray.dir_x);
	printf("dir_y %f\n", ray.dir_y);
	ray.sf_x = sqrtf(1 * powf(ray.dir_y/ray.dir_x, 2));
	ray.sf_y = sqrtf(1 * powf(ray.dir_x/ray.dir_y, 2));
	printf("scaling factor x %f\n", ray.sf_x);
	printf("scaling factor y %f\n", ray.sf_y);
	printf("dda int player x is %d\n", (int)data->player->coordinate->x);
	printf("dda int player y is %d\n", (int)data->player->coordinate->y);
	printf("dda float player x is %f\n", data->player->coordinate->x);
	printf("dda float player y is %f\n", data->player->coordinate->y);
	if (ray.dir_x < 0)
	{
		ray.step_x = -1;
		ray.len_x = (data->player->coordinate->x - (int)data->player->coordinate->x) * ray.step_x;
	}
	else
	{
		ray.step_x = 1;
		ray.len_x = (((int)data->player->coordinate->x + 1) - data->player->coordinate->x) * ray.step_x;
	}
	if (ray.dir_y < 0)
	{
		ray.step_y = -1;
		ray.len_y = (data->player->coordinate->y - (int)data->player->coordinate->y) * ray.step_y;
	}
	else
	{
		ray.step_y = 1;
		ray.len_y = (((int)data->player->coordinate->y + 1) - data->player->coordinate->y) * ray.step_y;
	}
	while (data->config->map[(int)][(int)])
	{
		if (ray.len_x < ray.len_y)
			data->player
	}
	// while (1)
	// {
	// 	ray.len_x 
	// }
	// printf("tan(angle) %f\n", tan(data->player->angle));
	data->rays = &ray;
}
