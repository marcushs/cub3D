/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:04:16 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/12 20:21:37 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_up(t_data *data)
{
	data->player->coordinate->y -= sin(data->player->angle) / 5;
	data->player->coordinate->x += cos(data->player->angle) / 5;
	init_player_hitbox(data->player);
}

void	move_left(t_data *data)
{
	data->player->coordinate->y -= cos(data->player->angle) / 5;
	data->player->coordinate->x -= sin(data->player->angle) / 5;
	init_player_hitbox(data->player);
}

void	move_right(t_data *data)
{
	data->player->coordinate->y += cos(data->player->angle) / 5;
	data->player->coordinate->x += sin(data->player->angle) / 5;
	init_player_hitbox(data->player);
}

void	move_down(t_data *data)
{
	data->player->coordinate->y += sin(data->player->angle) / 5;
	data->player->coordinate->x -= cos(data->player->angle) / 5;
	init_player_hitbox(data->player);
}
