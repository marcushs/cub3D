/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:04:56 by hleung            #+#    #+#             */
/*   Updated: 2023/11/11 17:17:25 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_player(t_player *player)
{
	player->coor.x = 0;
	player->coor.y = 0;
	player->dir.x = 0;
	player->dir.y = 0;
	player->view_dst_pos.x = 0;
	player->view_dst_pos.y = 0;
	player->angle = 0;
	player->ori = 0;
}

void	init_player_position(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	x = 0;
	y = 0;
	map = data->config.map;
	while (y < data->config.map_size && map[y])
	{
		while (x < (int)ft_strlen(map[y]) && map[y][x] && map[y][x] != '\n')
		{
			if (map[y][x] == N || map[y][x] == W \
			|| map[y][x] == S || map[y][x] == E)
			{
				data->player.ori = map[y][x];
				data->player.coor.y = ((float)y + 0.5) * data->cell_size;
				data->player.coor.x = ((float)x + 0.5) * data->cell_size;
			}
			x++;
		}
		x = 0;
		y++;
	}
	return ;
}

void	init_player_dir(t_data *data)
{
	if (data->player.ori == N)
	{
		data->player.dir.x = 0;
		data->player.dir.y = -1;
	}
	else if (data->player.ori == S)
	{
		data->player.dir.x = 0;
		data->player.dir.y = 1;
	}
	else if (data->player.ori == E)
	{
		data->player.dir.x = 1;
		data->player.dir.y = 0;
	}
	else if (data->player.ori == W)
	{
		data->player.dir.x = -1;
		data->player.dir.y = 0;
	}
}
