/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:48:27 by hleung            #+#    #+#             */
/*   Updated: 2023/10/20 11:20:57 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// static bool check_hitbox(char **map, t_player *player, int direction);
// static void	change_hitbox_moves(t_coor_f *moves, t_player *player, int direction);
static void	move_player_angle(int keycode, t_data *data);
static void	move_player_vert(int nb, t_data *data);
static void	move_player_hori(int nb, t_data *data);

void	move_player(int keycode, t_data *data)
{
	if (keycode == XK_w) //&& 
	// check_hitbox(data->config->map, data->player, XK_w) == true)
		move_player_vert(1, data);
	else if (keycode == XK_s) // && 
	// check_hitbox(data->config->map, data->player, XK_s) == true)
		move_player_vert(-1, data);
	else if (keycode == XK_a) // && 
	// check_hitbox(data->config->map, data->player, XK_a) == true)
		move_player_hori(1, data);
	else if (keycode == XK_d) // && 
	// check_hitbox(data->config->map, data->player, XK_d) == true)
		move_player_hori(-1, data);
	else if (keycode == XK_left)
		move_player_angle(XK_left, data);
	else if (keycode == XK_right)
		move_player_angle(XK_right, data);
	render_minimap(data, data->mlx, data->config, data->player->coordinate);
	return ;
}

// static bool check_hitbox(char **map, t_player *player, int direction)
// {
// 	t_coor_f	moves;

// 	moves.x = 0.0;
// 	moves.y = 0.0;
// 	change_hitbox_moves(&moves, player, direction);
// 	if (map[(int)(player->t_left->y + moves.y)] 
// 	[(int)(player->t_left->x + moves.x)] == '1')
// 		return (false);
// 	if (map[(int)(player->t_right->y + moves.y)] 
// 	[(int)(player->t_right->x + moves.x)] == '1')
// 		return (false);
// 	if (map[(int)(player->b_left->y + moves.y)] 
// 	[(int)(player->b_left->x + moves.x)] == '1')
// 		return (false);
// 	if (map[(int)(player->b_right->y + moves.y)] 
// 	[(int)(player->b_right->x + moves.x)] == '1')
// 		return (false);
// 	return true;
// }

// static void	change_hitbox_moves(t_coor_f *moves, t_player *player, int direction)
// {
// 	if (direction == XK_w)
// 	{
// 		moves->x = cos(player->angle) / 5;
// 		moves->y -= sin(player->angle) / 5;
// 	}
// 	else if (direction == XK_s)
// 	{
// 		moves->x -= cos(player->angle) / 5;
// 		moves->y = sin(player->angle) / 5;
// 	}
// 	else if (direction == XK_a)
// 	{
// 		moves->x -= sin(player->angle) / 5;
// 		moves->y -= cos(player->angle) / 5;
// 	}
// 	else if (direction == XK_d)
// 	{
// 		moves->x = sin(player->angle) / 5;
// 		moves->y = cos(player->angle) / 5;
// 	}
// 	return ;
// }


static void	move_player_vert(int nb, t_data *data)
{
	// if (keycode == XK_w)
	// {
	// 	// data->player->coordinate->y -= sin(data->player->angle) / 5;
	// 	// data->player->coordinate->x += cos(data->player->angle) / 5;
	// 	// init_player_hitbox(data->player);
	// }
	// else if (keycode == XK_s)
	// {
	// 	// data->player->coordinate->y += sin(data->player->angle) / 5;
	// 	// data->player->coordinate->x -= cos(data->player->angle) / 5;
	// 	// init_player_hitbox(data->player);
	// }
	// else if (keycode == XK_a)
	// {
	// 	// data->player->coordinate->y -= cos(data->player->angle) / 5;
	// 	// data->player->coordinate->x -= sin(data->player->angle) / 5;
	// 	// init_player_hitbox(data->player);
	// }
	// else if (keycode == XK_d)
	// {
	// 	// data->player->coordinate->y += cos(data->player->angle) / 5;
	// 	// data->player->coordinate->x += sin(data->player->angle) / 5;
	// 	// init_player_hitbox(data->player);
	// }static bool check_hitbox(char **map, t_player *player, int direction);
// static void	change_hitbox_moves(t_coor_f *moves, t_player *player, int direction);
	float tmp_x;
	float tmp_y;
	
	tmp_x = data->player->coordinate->x + cos(data->player->angle) * data->player->mv_speed * nb;
	if (data->config->map[(int)data->player->coordinate->y][(int)tmp_x] != '1')
		data->player->coordinate->x = tmp_x;
	tmp_y = data->player->coordinate->y - sin(data->player->angle) * data->player->mv_speed * nb;
	if (data->config->map[(int)tmp_y][(int)data->player->coordinate->x] != '1')
		data->player->coordinate->y = tmp_y;
	return ;
}

static void	move_player_hori(int nb, t_data *data)
{
	float tmp_x;
	float tmp_y;
	
	tmp_x = data->player->coordinate->x - cos(data->player->angle - 0.5 * PI) * data->player->mv_speed * nb;
	if (data->config->map[(int)data->player->coordinate->y][(int)tmp_x] != '1')
		data->player->coordinate->x = tmp_x;
	tmp_y = data->player->coordinate->y + sin(data->player->angle - 0.5 * PI) * data->player->mv_speed * nb;
	if (data->config->map[(int)tmp_y][(int)data->player->coordinate->x] != '1')
		data->player->coordinate->y = tmp_y;
	return ;
}

static void	move_player_angle(int keycode, t_data *data)
{
	if (keycode == XK_left)
		data->player->angle += 0.05;
	else if (keycode == XK_right)
		data->player->angle -= 0.05;
	return ;
}
