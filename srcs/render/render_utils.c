/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:32:07 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/19 21:48:59 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	map_longest_row(t_config *config)
{
	int max;
	int len;
	int y;

	max = 0;
	y = -1;
	while (++y < config->map_size)
	{
		len = 0;
		while (config->map[y][len] && config->map[y][len] != '\n')
			len++;
		if (len > max)
			max = len;
	}
	return (max);
}

void	init_image_data(t_mlx *mlx, t_config *config)
{
	config->map_row = map_longest_row(config);
	mlx->mini_map->width = (config->map_row + 1) * 15;
	mlx->mini_map->height = (config->map_size + 1) * 15;
	mlx->mini_map->img = mlx_new_image(mlx->mlx, \
	mlx->mini_map->width, mlx->mini_map->height);
	mlx->mini_map->img_addr = mlx_get_data_addr(mlx->mini_map->img, \
	&mlx->mini_map->bpp, &mlx->mini_map->line_len, &mlx->mini_map->endian);
	mlx->window->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->window->img_addr = mlx_get_data_addr(mlx->window->img, \
	&mlx->window->bpp, &mlx->window->line_len, &mlx->window->endian);
	mlx->player->img = mlx_new_image(mlx->mlx, PLAYER_WIDTH, PLAYER_HEIGHT);
	mlx->player->img_addr = mlx_get_data_addr(mlx->player->img, \
	&mlx->player->bpp, &mlx->player->line_len, &mlx->player->endian);
	return ;
}
