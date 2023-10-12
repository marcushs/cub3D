/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:48:27 by hleung            #+#    #+#             */
/*   Updated: 2023/10/12 20:44:36 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	turn_right(t_data *data);
static void	turn_left(t_data *data);

void	move_player(int keycode, t_data *data)
{
	if (keycode == XK_w && \
	check_hitbox(data->config->map, data->player, XK_w) == true)
		move_up(data);
	else if (keycode == XK_d && \
	check_hitbox(data->config->map, data->player, XK_d) == true)
		move_right(data);
	else if (keycode == XK_s && \
	check_hitbox(data->config->map, data->player, XK_s) == true)
		move_down(data);
	else if (keycode == XK_a && \
	check_hitbox(data->config->map, data->player, XK_a) == true)
		move_left(data);
	else if (keycode == XK_left)
		turn_left(data);
	else if (keycode == XK_right)
		turn_right(data);
	render_minimap(data);
}

static void	turn_left(t_data *data)
{
	data->player->angle += 0.1;
}

static void	turn_right(t_data *data)
{
	data->player->angle -= 0.1;
}
