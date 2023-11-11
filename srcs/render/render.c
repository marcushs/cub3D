/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/11 09:15:11 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	render_border(t_data *data);

void	mlx_clear_image(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W)
		{
			put_pixel(mlx->mmb, x, y, 0x00000);
			x++;
		}
		y++;
	}
	return ;
}

void	put_window_image_to_window(t_data *data, float x, float y)
{
	t_mlx	*m;

	m = &data->mlx;
	mlx_clear_image(m);
	ft_put_img_to_img(m->mmb, m->mini_map, 90 - x * 15 , 90 - y * 15);
	render_border(data);
	ft_put_img_to_img(m->mmb, m->player, 100, 100);
	ft_put_img_to_img(m->window, m->mmb, 30, 30);
	mlx_put_image_to_window(m->mlx, m->mlx_win, m->window->img, 0, 0);
	return ;
}
void	render_border(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W)
		{
			if (x < 2 || y < 2 || y > MAP_H - 2 || x > MAP_W - 2)
				put_pixel(data->mlx.mmb, x, y, 0x8395a7);
			x++;
		}
		y++;
	}
	return ;
}

void render_minimap(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->config.map_size)
	{
		x = 0;
		while (data->config.map[y][x] && data->config.map[y][x] != '\n')
		{
			if (data->config.map[y][x] == '1')
				put_square(&data->mlx, x, y, 0);
			x++;
		}
		y++;
	}
	return;
}

void render_player(t_image *player)
{
	int	x;
	int	y;

	y = 0;

	while (y < 8)
	{
		x = 0;
		while (x < 8)
			put_pixel(player, x++, y, 0x00FF0000);
		y++;
	}
	return ;
}

void	render_floor_ceiling(t_data *data)
{
	int		i;
	int		floor_start;
	int		size;
	char	*dst;

	i = 0;
	floor_start = WIN_W * (WIN_H * 0.5);
	size = data->mlx.window->bpp / 8;
	dst = NULL;
	while (i < WIN_H * WIN_W)
	{
		if (i >= 0 && i < floor_start)
		{
			dst = data->mlx.window->img_addr + i * size;
			*(unsigned int *)dst = data->ceiling_color;
		}
		else if (i >= 0 && i > floor_start)
		{
			dst = data->mlx.window->img_addr + i * size;
			*(unsigned int *)dst = data->floor_color;
		}
		i++;
	}
}
