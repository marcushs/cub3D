/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:20:45 by hleung            #+#    #+#             */
/*   Updated: 2023/10/18 16:16:34 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
void draw_line_color(t_data *data, float x1, float y1, float x2, float y2, int color);

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
	int				side;
	float			perpWallDist;
	// int				hit_axis;
	int	map_x;
	int	map_y;
	int	ratio;
	int	pix;

	start.x = data->player->coordinate->x;
	start.y = data->player->coordinate->y;
	map_x = start.x;
	map_y = start.y;
	
	pix = 0;
	while (pix++ < 128)
	{
		ratio = (pix - 64)/ 64;
		dir.x = cos(data->player->angle) / 2 + cos(data->player->angle - 0.25) * ratio;
		dir.y = sin(data->player->angle) / 2 + sin(data->player->angle - 0.25) * ratio;
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
				// start.x += dir.x;
				// hit_axis = 0;
				side = 0;
			}
			else
			{
				map_y += step_y;
				ray_len_1d.y += unit_step.y;
				// start.y += dir.y;
				// hit_axis = 1;
				side = 1;
			}
			if (data->config->map[map_y][map_x] == '1')
			{
				hit = 1;
				return ;
			}
			if (side == 0)
				perpWallDist = (map_x - data->player->coordinate->x + (1 - step_x) / 2) / dir.x;
			else
				perpWallDist = (map_y - data->player->coordinate->y + (1 - step_y) / 2) / dir.y;
			int	wallcolor = (side == 0) ? 0x0000FFFF : 0x00DD88BB;
			draw_line_color(data, pix, 64-32/perpWallDist, pix, 64+32/perpWallDist, wallcolor);
		}
	}
	// plane.x = 0; // sin(data->player->angle);
	// plane.y = 0.66;
	// data->rays[data->r_idx++] = ray;
}

void draw_line_color(t_data *data, float x1, float y1, float x2, float y2, int color)
{
	for (float i = 0.0f; i < 1.0f; i += .0005f)
	{
		int	x = x1 + (x2 - x1) * i;
		int y = y1 + (y2 - y1) * i;
		put_pixel(data->mlx->mlx, x, y, color);
	}
}
