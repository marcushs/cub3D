// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   move.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/10/05 17:48:27 by hleung            #+#    #+#             */
// /*   Updated: 2023/10/27 11:48:35 by tduprez          ###   ########lyon.fr   */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/cub3D.h"

int		is_walkable(t_data *data, float x, float y);
// static bool check_hitbox(char **map, t_player *player, int direction);
// static void	change_hitbox_moves(t_coordinate *moves, t_player *player, int direction);
// static void	move_player_angle(int keycode, t_data *data);
// static void	move_player_direction(int keycode, t_data *data);

// void	move_player(int keycode, t_data *data)
// {
// 	if (keycode == XK_w && 
// 	check_hitbox(data->config->map, data->player, XK_w) == true)
// 		move_player_direction(XK_w, data);
// 	else if (keycode == XK_s && 
// 	check_hitbox(data->config->map, data->player, XK_s) == true)
// 		move_player_direction(XK_s, data);
// 	else if (keycode == XK_a && 
// 	check_hitbox(data->config->map, data->player, XK_a) == true)
// 		move_player_direction(XK_a, data);
// 	else if (keycode == XK_d && 
// 	check_hitbox(data->config->map, data->player, XK_d) == true)
// 		move_player_direction(XK_d, data);
// 	else if (keycode == XK_left)
// 		move_player_angle(XK_left, data);
// 	else if (keycode == XK_right)
// 		move_player_angle(XK_right, data);
// 	dda(data);
// 	put_window_image_to_window(data->mlx, data->player->coor->x, 
// 	data->player->coor->y);
// 	return ;
// }

// static bool check_hitbox(char **map, t_player *player, int direction)
// {
// 	t_coordinate	moves;

// 	moves.x = 0.0;
// 	moves.y = 0.0;
// 	change_hitbox_moves(&moves, player, direction);
// 	if (map[(int)(player->t_left.y + moves.y)] 
// 	[(int)(player->t_left.x + moves.x)] == '1')
// 		return (false);
// 	if (map[(int)(player->t_right.y + moves.y)] 
// 	[(int)(player->t_right.x + moves.x)] == '1')
// 		return (false);
// 	if (map[(int)(player->b_left.y + moves.y)] 
// 	[(int)(player->b_left.x + moves.x)] == '1')
// 		return (false);
// 	if (map[(int)(player->b_right.y + moves.y)] 
// 	[(int)(player->b_right.x + moves.x)] == '1')
// 		return (false);
// 	return true;
// }

// static void	change_hitbox_moves(t_coordinate *moves, t_player *player, int direction)
// {
// 	if (direction == XK_w)
// 	{
// 		moves->y = sin(player->angle) * 0.25;
// 		moves->x -= cos(player->angle) * 0.25;
// 	}
// 	else if (direction == XK_s)
// 	{
// 		moves->y -= sin(player->angle) * 0.25;
// 		moves->x = cos(player->angle) * 0.25;
// 	}
// 	else if (direction == XK_a)
// 	{
// 		moves->y -= cos(player->angle) * 0.25;
// 		moves->x = sin(player->angle) * 0.25;
// 	}
// 	else if (direction == XK_d)
// 	{
// 		moves->y = cos(player->angle) * 0.25;
// 		moves->x -= sin(player->angle) * 0.25;
// 	}
// 	return ;
// }


// static void	move_player_direction(int keycode, t_data *data)
// {
// 	if (keycode == XK_w)
// 	{
// 		data->player->coor->y += sin(data->player->angle) * 0.25;
// 		data->player->coor->x -= cos(data->player->angle) * 0.25;
// 		init_player_hitbox(data->player);
// 	}
// 	else if (keycode == XK_s)
// 	{
// 		data->player->coor->y -= sin(data->player->angle) * 0.25;
// 		data->player->coor->x += cos(data->player->angle) * 0.25;
// 		init_player_hitbox(data->player);
// 	}
// 	else if (keycode == XK_a)
// 	{
// 		data->player->coor->y -= cos(data->player->angle) * 0.25;
// 		data->player->coor->x += sin(data->player->angle) * 0.25;
// 		init_player_hitbox(data->player);
// 	}
// 	else if (keycode == XK_d)
// 	{
// 		data->player->coor->y += cos(data->player->angle) * 0.25;
// 		data->player->coor->x -= sin(data->player->angle) * 0.25;
// 		init_player_hitbox(data->player);
// 	}
// 	return ;
// }

// static void	move_player_angle(int keycode, t_data *data)
// {
// 	if (keycode == XK_left)
// 		data->player->angle += 0.1;
// 	else if (keycode == XK_right)
// 		data->player->angle -= 0.1;
// 	return ;
// }

void	move_forward(t_data *data)
{
	t_coor_f	tmp_coor;
	t_coor_f	*p_pos;
	
	p_pos = &data->player.coor;
	tmp_coor.x = p_pos->x + data->player.dir.x * data->move_speed;
	tmp_coor.y = p_pos->y + data->player.dir.y * data->move_speed;
	if (is_walkable(data, tmp_coor.x, p_pos->y))
		p_pos->x = tmp_coor.x;
	if (is_walkable(data, p_pos->x, tmp_coor.y))
		p_pos->y = tmp_coor.y;
}

void	move_backward(t_data *data)
{
	t_coor_f	tmp_coor;
	t_coor_f	*p_pos;
	
	p_pos = &data->player.coor;
	tmp_coor.x = p_pos->x - data->player.dir.x * data->move_speed;
	tmp_coor.y = p_pos->y - data->player.dir.y * data->move_speed;
	if (is_walkable(data, tmp_coor.x, p_pos->y))
		p_pos->x = tmp_coor.x;
	if (is_walkable(data, p_pos->x, tmp_coor.y))
		p_pos->y = tmp_coor.y;
}

void	move_left(t_data *data)
{
	t_coor_f	tmp_coor;
	t_coor_f	new_dir;
	t_coor_f	*p_pos;

	p_pos = &data->player.coor;
	new_dir.x = data->player.dir.x * cos(-PI / 2) - data->player.dir.y * sin(-PI / 2);
	new_dir.y = data->player.dir.x * sin(-PI / 2) + data->player.dir.y * cos(-PI / 2);
	tmp_coor.x = new_dir.x * data->move_speed + p_pos->x;
	tmp_coor.y = new_dir.y * data->move_speed + p_pos->y;
	if (is_walkable(data, tmp_coor.x, p_pos->y))
		p_pos->x = tmp_coor.x;
	if (is_walkable(data, p_pos->x, tmp_coor.y))
		p_pos->y = tmp_coor.y;
}

void	move_right(t_data *data)
{
	t_coor_f	tmp_coor;
	t_coor_f	new_dir;
	t_coor_f	*p_pos;

	p_pos = &data->player.coor;
	new_dir.x = data->player.dir.x * cos(PI / 2) - data->player.dir.y * sin(PI / 2);
	new_dir.y = data->player.dir.x * sin(PI / 2) + data->player.dir.y * cos(PI / 2);
	tmp_coor.x = new_dir.x * data->move_speed + p_pos->x;
	tmp_coor.y = new_dir.y * data->move_speed + p_pos->y;
	if (is_walkable(data, tmp_coor.x, p_pos->y))
		p_pos->x = tmp_coor.x;
	if (is_walkable(data, p_pos->x, tmp_coor.y))
		p_pos->y = tmp_coor.y;
}

void	rotate_right(t_data *data)
{
	double old_dir_x;
	
	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(data->rot_speed) - data->player.dir.y * sin(data->rot_speed);
	data->player.dir.y = old_dir_x * sin(data->rot_speed) + data->player.dir.y * cos(data->rot_speed);
}
void	rotate_left(t_data *data)
{
	double old_dir_x;
	
	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(-data->rot_speed) - data->player.dir.y * sin(-data->rot_speed);
	data->player.dir.y = old_dir_x * sin(-data->rot_speed) + data->player.dir.y * cos(-data->rot_speed);
}

int	is_walkable(t_data *data, float x, float y)
{
	t_coor_i	cell;

	cell.x = x / data->cell_size;
	cell.y = y / data->cell_size;
	if (cell.x < 0 || cell.x > data->config.map_row - 1)
		return (0);
	if (cell.y < 0 || cell.y > data->config.map_size - 1)
		return (0);
	if (data->config.map[cell.y][cell.x] != '1')
		return (1);
	return (0);
}
