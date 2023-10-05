/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:29:49 by hleung            #+#    #+#             */
/*   Updated: 2023/10/05 17:41:41 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	render_minimap(t_data *data);
int		map_longest_row(t_data *data);
void	put_square(t_mlx *mlx, int w, int h, int color);
void	put_player(t_mlx *mlx, int x, int y, int color);

void	config_init(t_config *config)
{
	config->fd = -1;
	config->path_to_no = NULL;
	config->path_to_so = NULL;
	config->path_to_we = NULL;
	config->path_to_ea = NULL;
	config->map_tmp = NULL;
	config->map_list = NULL;
	config->map_size = 0;
	config->map_row = 0;
	config->map = NULL;
}

// void	data_init(t_data *data)
// {
// 	// data->pi = 3.14;
// 	// data->x_case = 20;
// 	// data->y_case = 15;
// 	// data->block_size = 64;
// 	// data->width_screen = data->x_case * data->block_size;
// 	// data->height_screen = data->y_case * data->block_size;
// 	return ;
// }

void	t_mlx_init(t_mlx *mlx, t_data *data)
{
	(void)data;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 2500, 1500, "Cub3D");
	mlx->mini_map = NULL;
	mlx->player = NULL;
	mlx->addr = NULL;
	render_minimap(data);
	return ;
}

void	render_minimap(t_data *data)
{
	int	x;
	int	y;
	
	data->config->map_row = map_longest_row(data);
	data->mlx->mini_map = mlx_new_image(data->mlx->mlx,(data->config->map_row + 1) * 15, (data->config->map_size + 1) * 15);
	data->mlx->player = mlx_new_image(data->mlx->mlx, 7, 7);
	data->mlx->addr = mlx_get_data_addr(data->mlx->mini_map, &data->mlx->bits_per_pixel, &data->mlx->line_length, &data->mlx->endian);
	y = 0;
	while (y < data->config->map_size)
	{
			printf("%s", data->config->map[y]);
		x = 0;
		while (data->config->map[y][x] && data->config->map[y][x] != '\n')
		{
			if (data->config->map[y][x] == '1')
				put_square(data->mlx, x, y, 0x00999999);
			if (data->config->map[y][x] == 'N')
				put_player(data->mlx, x, y, 0x00FF0000);
			// else if (data->config->map[y][x] == '0')
			// 	put_square(data->mlx, x, y, 0x00263138);
			// else if (data->config->map[y][x] == ' ')
			// 	put_square(data->mlx, x, y, 0x00000000);
			// else if (data->config->map[y][x] == 'N')
			// 	put_square(data->mlx, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->mini_map, 0, 0);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->player, 0, 0);
	mlx_destroy_image(data->mlx->mlx, data->mlx->mini_map);
	mlx_destroy_image(data->mlx->mlx, data->mlx->player);
}

void	put_square(t_mlx *mlx, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = (x + 1) * 15;
	start_y = (y + 1) * 15;
	end_x = start_x + 14;
	end_y = start_y + 14;
	while (start_y < end_y)
	{
		while (start_x < end_x)
		{
			my_mlx_pixel_put(mlx, start_x, start_y, color);
			start_x++;
		}
		start_x -= 14;
		start_y++;
	}
}

void	put_player(t_mlx *mlx, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = (x + 1) * 15 + 5;
	start_y = (y + 1) * 15 + 5;
	end_x = start_x + 6;
	end_y = start_y + 6;
	while (start_y < end_y)
	{
		while (start_x < end_x)
		{
			my_mlx_pixel_put(mlx, start_x, start_y, color);
			start_x++;
		}
		start_x -= 6;
		start_y++;
	}
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	map_longest_row(t_data *data)
{
	int	max;
	int	len;
	int	y;

	max = 0;
	y = -1;
	while (++y < data->config->map_size)
	{
		len = 0;
		while (data->config->map[y][len] && data->config->map[y][len] != '\n')
			len++;
		if (len > max)
			max = len;
	}
	return (max);
}
