/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/05 17:48:29 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define POS_X 500
#define POS_Y 600

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_mlx *img)
{
	for (int i = get_player_address(NULL)->pos_y; i < get_player_address(NULL)->pos_y + 15; i++)
	{
		for (int j = get_player_address(NULL)->pos_x; j < get_player_address(NULL)->pos_x + 15; j++)
			my_mlx_pixel_put(img, j, i, 0x00FF0000);
	}
}

void	draw_background(t_mlx *img)
{
	for (int i = 0; i < 1080; i++)
	{
		for (int j = 0; j < 1920; j++)
			my_mlx_pixel_put(img, j, i, 0x00FF000000);
	}
}

int	mapX = 10, mapY = 10, mapS = 100;

int	map[10][10] =
				{
					{ 1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,1,0,0,0,0,0,0,1 },
					{ 1,0,1,0,0,1,1,1,1,1 },
					{ 1,0,0,0,0,1,0,0,0,1 },
					{ 1,1,0,0,0,1,1,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,1 },
					{ 1,1,1,1,1,1,1,1,1,1 },
				};

void	put_square(t_mlx* img, int x, int y, int type)
{
	int	tmp_x = x;
	int	tmp_y = y;
	while (y < tmp_y + 191)
	{
		x = tmp_x;
		while (x < tmp_x + 191)
		{
			if (type == 1)
				my_mlx_pixel_put(img, x, y, 0x999999);
			else
				my_mlx_pixel_put(img, x, y, 0x00FF000000);
			x++;
		}
		y++;
	}
}

void	draw_map(t_mlx* img)
{
	int	x = 0;
	int	y = 0;

	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			put_square(img, x * 192, y * 192, map[y][x]);
		}
	}
}

void	raycasting(t_config *config)
{
	t_data		data;
	t_mlx		mlx;
	t_player	player;

	player.pos_x = POS_X;
	player.pos_y = POS_Y;
	get_config_address(config);
	get_data_address(&data);
	get_mlx_address(&mlx);
	get_player_address(&player);
	(void)config;
	data_init(&data);
	t_mlx_init(&mlx, &data);

	mlx_hook(mlx.mlx_win, 17, 0, &event_close, &mlx);
	mlx_hook(mlx.mlx_win, 2, (1L<<0), &event_move, &mlx);
	mlx_loop_hook(mlx.mlx, &event_key_hook, &data);
	mlx.img = mlx_new_image(mlx.mlx, 1920, 1920);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
								&mlx.endian);
	draw_map(&mlx);
	draw_square(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);

}
