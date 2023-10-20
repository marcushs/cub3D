/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:20:45 by hleung            #+#    #+#             */
/*   Updated: 2023/10/20 11:30:53 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
void draw_line_color(t_data *data, t_coor_i p1, t_coor_i p2, int color);

void	dda(t_data *data)
{
	// t_ray	ray;
	t_coor_f	start;
	t_coor_f	dir;
	t_coor_f	unit_step;
	t_coor_f	ray_len_1d;
	t_coor_i	p1;
	t_coor_i	p2;
	int				step_x;
	int				step_y;
	int				side;
	float			perpWallDist;
	int	map_x;
	int	map_y;
	float	ratio;
	int	pix;
	float	half_win_w;
	float	half_win_h;
	int	wallcolor;
	
	start.x = data->player->coordinate->x;
	start.y = data->player->coordinate->y;
	map_x = start.x;
	map_y = start.y;
	
	pix = 0;
	half_win_w = WIN_W * 0.5;
	half_win_h = WIN_H * 0.5;
	while (pix < WIN_W)
	{
		ratio = (pix - half_win_w)/ half_win_w;
		dir.x = cos(data->player->angle) / 2 + cos(data->player->angle - 0.5 * PI) * ratio;
		dir.y = sin(data->player->angle) / 2 + sin(data->player->angle - 0.5 * PI) * ratio;
		if (dir.x == 0)
			unit_step.x = 1e30;
		else 
			unit_step.x = sqrtf(1 + powf((dir.y / dir.x), 2));
		if (dir.y == 0)
			unit_step.y = 1e30;
		else
			unit_step.y = sqrtf(1 + powf((dir.x / dir.y), 2));
		if (dir.x < 0)
		{
			step_x = -1;
			ray_len_1d.x = (start.x - (float)map_x) * unit_step.x;
		}
		else
		{
			step_x = 1;
			ray_len_1d.x = ((float)(map_x + 1) - start.x) * unit_step.x;
		}
		if (dir.y < 0)
		{
			step_y = -1;
			ray_len_1d.y = (start.y - (float)map_y) * unit_step.y;
		}
		else
		{
			step_y = 1;
			ray_len_1d.y = ((float)(map_y + 1) - start.y) * unit_step.y;
		}
		// float max_len = 8.0;
		int	hit = 0;
		while (!hit && map_x < (data->config->map_row - 1) && map_x >= 0 && map_y < (data->config->map_size - 1) && map_y >= 0)
		{
			if (ray_len_1d.y <= 0 || (ray_len_1d.x >= 0 && ray_len_1d.x < ray_len_1d.y))
			{
				map_x += step_x;
				ray_len_1d.x += unit_step.x;
				side = 0;
			}
			else
			{
				map_y += step_y;
				ray_len_1d.y += unit_step.y;
				side = 1;
			}
			if (data->config->map[map_y][map_x] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (map_x - data->player->coordinate->x + (1 - step_x) / 2) / dir.x;
		else
			perpWallDist = (map_y - data->player->coordinate->y + (1 - step_y) / 2) / dir.y;
		wallcolor = (side == 0) ? 0x0000FFFF : 0x00DD88BB;
		p1.x = pix;
		p1.y = half_win_h - half_win_h * 0.5/perpWallDist;
		p2.x = pix;
		p2.y = half_win_h + half_win_h * 0.5/perpWallDist;
		draw_line_color(data, p1, p2, wallcolor);
		// printf("%d\n", pix);
		// printf("angle %f\n", data->player->angle);
		pix++;
	}
	// plane.x = 0; // sin(data->player->angle);
	// plane.y = 0.66;
	// data->rays[data->r_idx++] = ray;
}
void draw_line_color(t_data *data, t_coor_i p1, t_coor_i p2, int color)
{
	for (float i = 0.0f; i < 1.0f; i += .0005f)
	{
		int	x = p1.x + (p2.x - p1.x) * i;
		int y = p1.y + (p2.y - p1.y) * i;
		put_pixel(data->mlx, x, y, color);
	}
}
