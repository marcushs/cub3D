/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:48:27 by hleung            #+#    #+#             */
/*   Updated: 2023/10/19 22:05:33 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static bool check_hitbox(char **map, t_player *player, int direction);
static void	change_hitbox_moves(t_coordinate *moves, t_player *player, int direction);
static void	move_player_angle(int keycode, t_data *data);
static void	move_player_direction(int keycode, t_data *data);

void	move_player(int keycode, t_data *data)
{
	if (keycode == XK_w && \
	check_hitbox(data->config->map, data->player, XK_w) == true)
		move_player_direction(XK_w, data);
	else if (keycode == XK_s && \
	check_hitbox(data->config->map, data->player, XK_s) == true)
		move_player_direction(XK_s, data);
	else if (keycode == XK_a && \
	check_hitbox(data->config->map, data->player, XK_a) == true)
		move_player_direction(XK_a, data);
	else if (keycode == XK_d && \
	check_hitbox(data->config->map, data->player, XK_d) == true)
		move_player_direction(XK_d, data);
	else if (keycode == XK_left)
		move_player_angle(XK_left, data);
	else if (keycode == XK_right)
		move_player_angle(XK_right, data);
	put_window_image_to_window(data->mlx, data->player->coordinate->x, \
	data->player->coordinate->y);
	return ;
}

static bool check_hitbox(char **map, t_player *player, int direction)
{
	t_coordinate	moves;

	moves.x = 0.0;
	moves.y = 0.0;
	change_hitbox_moves(&moves, player, direction);
	if (map[(int)(player->t_left->y + moves.y)] \
	[(int)(player->t_left->x + moves.x)] == '1')
		return (false);
	if (map[(int)(player->t_right->y + moves.y)] \
	[(int)(player->t_right->x + moves.x)] == '1')
		return (false);
	if (map[(int)(player->b_left->y + moves.y)] \
	[(int)(player->b_left->x + moves.x)] == '1')
		return (false);
	if (map[(int)(player->b_right->y + moves.y)] \
	[(int)(player->b_right->x + moves.x)] == '1')
		return (false);
	return true;
}

static void	change_hitbox_moves(t_coordinate *moves, t_player *player, int direction)
{
	if (direction == XK_w)
	{
		moves->y = sin(player->angle) * 0.25;
		moves->x -= cos(player->angle) * 0.25;
	}
	else if (direction == XK_s)
	{
		moves->y -= sin(player->angle) * 0.25;
		moves->x = cos(player->angle) * 0.25;
	}
	else if (direction == XK_a)
	{
		moves->y -= cos(player->angle) * 0.25;
		moves->x = sin(player->angle) * 0.25;
	}
	else if (direction == XK_d)
	{
		moves->y = cos(player->angle) * 0.25;
		moves->x -= sin(player->angle) * 0.25;
	}
	return ;
}


static void	move_player_direction(int keycode, t_data *data)
{
	if (keycode == XK_w)
	{
		data->player->coordinate->y += sin(data->player->angle) * 0.25;
		data->player->coordinate->x -= cos(data->player->angle) * 0.25;
		init_player_hitbox(data->player);
	}
	else if (keycode == XK_s)
	{
		data->player->coordinate->y -= sin(data->player->angle) * 0.25;
		data->player->coordinate->x += cos(data->player->angle) * 0.25;
		init_player_hitbox(data->player);
	}
	else if (keycode == XK_a)
	{
		data->player->coordinate->y -= cos(data->player->angle) * 0.25;
		data->player->coordinate->x += sin(data->player->angle) * 0.25;
		init_player_hitbox(data->player);
	}
	else if (keycode == XK_d)
	{
		data->player->coordinate->y += cos(data->player->angle) * 0.25;
		data->player->coordinate->x -= sin(data->player->angle) * 0.25;
		init_player_hitbox(data->player);
	}
	return ;
}

static void	move_player_angle(int keycode, t_data *data)
{
	if (keycode == XK_left)
		data->player->angle += 0.1;
	else if (keycode == XK_right)
		data->player->angle -= 0.1;
	return ;
}
