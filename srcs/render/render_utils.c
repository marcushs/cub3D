/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:32:07 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/14 13:15:20 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	free_errors(t_config *config, t_mlx *mlx, t_data *data);

int	map_longest_row(t_config *config)
{
	int	max;
	int	len;
	int	y;

	max = 0;
	y = -1;
	while (++y < config->map_size)
	{
		len = 0;
		while (config->map[y][len] && config->map[y][len] != 'n')
			len++;
		if (len > max)
			max = len;
	}
	return (max);
}

void	init_image_data(t_mlx *mlx, t_config *config, t_data *data)
{
	config->map_row = map_longest_row(config);
	mlx->mini_map->width = (config->map_row + 1) * 15;
	mlx->mini_map->height = (config->map_size + 1) * 15;
	mlx->mini_map->img = mlx_new_image(mlx->mlx, \
	mlx->mini_map->width, mlx->mini_map->height);
	if (!mlx->mini_map->img)
		free_errors(config, mlx, data);
	mlx->mini_map->img_addr = mlx_get_data_addr(mlx->mini_map->img, \
	&mlx->mini_map->bpp, &mlx->mini_map->line_len, &mlx->mini_map->endian);
	mlx->mmb->img = mlx_new_image(mlx->mlx, MAP_W, MAP_H);
	if (!mlx->mmb->img)
		free_errors(config, mlx, data);
	mlx->mmb->img_addr = mlx_get_data_addr(mlx->mmb->img, \
	&mlx->mmb->bpp, &mlx->mmb->line_len, &mlx->mmb->endian);
	mlx->window->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	if (!mlx->window->img)
		free_errors(config, mlx, data);
	mlx->window->img_addr = mlx_get_data_addr(mlx->window->img, \
	&mlx->window->bpp, &mlx->window->line_len, &mlx->window->endian);
	mlx->player->img = mlx_new_image(mlx->mlx, PLAYER_W, PLAYER_H);
	if (!mlx->player->img)
		free_errors(config, mlx, data);
	mlx->player->img_addr = mlx_get_data_addr(mlx->player->img, \
	&mlx->player->bpp, &mlx->player->line_len, &mlx->player->endian);
	return ;
}

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

static void	free_errors(t_config *config, t_mlx *mlx, t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->textures[i].text)
			mlx_destroy_image(mlx->mlx, data->textures[i].text);
	}
	if (mlx->mmb->img)
		mlx_destroy_image(mlx->mlx, mlx->mmb->img);
	if (mlx->mini_map->img)
		mlx_destroy_image(mlx->mlx, mlx->mini_map->img);
	if (mlx->player->img)
		mlx_destroy_image(mlx->mlx, mlx->player->img);
	if (mlx->window->img)
		mlx_destroy_image(mlx->mlx, mlx->window->img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free_data(data);
	free_config_exit_msg(config, EXIT_FAILURE, MLX_ERR);
	return ;
}
