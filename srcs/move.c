/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:48:27 by hleung            #+#    #+#             */
/*   Updated: 2023/10/12 13:08:10 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_up(t_data *data);
void	move_right(t_data *data);
void	move_down(t_data *data);
void	move_left(t_data *data);


// float	get_direction_vector_length(t_data *data, bool is_inverse)
// {
// 	float	vector_x = data->player->coordinate->x;
// 	float	vector_y = data->player->coordinate->y;
// 	float	step_size = 0.05;
// 	float	res = 0;

// 	(void)is_inverse;
// 	while (data->config->map[(int)vector_y] && data->config->map[(int)vector_y][(int)vector_x] != '1')
// 	{
// 		if (is_inverse == true)
// 		{
// 			vector_x -= cos(data->player->angle) * step_size;
// 			vector_y += sin(data->player->angle) * step_size;
// 		}
// 		else
// 		{
// 			vector_x += cos(data->player->angle) * step_size;
// 			vector_y -= sin(data->player->angle) * step_size;
// 		}
// 		res += 0.05;
// 	}
// 	return (res);
// }

bool	check_hitbox(char **map, t_player *p, bool is_up)
{
	if (is_up == true)
	{
		if (map[(int)((p->top_left->y - sin(p->angle) / 5) - 0.15)]\
		[(int)((p->top_left->x + cos(p->angle) / 5) - 0.15)] == '1')
			return (false);
		if (map[(int)((p->top_right->y - sin(p->angle) / 5) - 0.15)]\
		[(int)((p->top_right->x + cos(p->angle) / 5) + 0.15)] == '1')
			return (false);
		if (map[(int)((p->bottom_left->y - sin(p->angle) / 5) + 0.15)]\
		[(int)((p->bottom_left->x + cos(p->angle) / 5) - 0.15)] == '1')
			return (false);
		if (map[(int)((p->bottom_right->y - sin(p->angle) / 5) + 0.15)]\
		[(int)((p->bottom_right->x + cos(p->angle) / 5) + 0.15)] == '1')
			return (false);
	}
	else
	{
		if (map[(int)((p->top_left->y + sin(p->angle) / 5) - 0.15)]\
		[(int)((p->top_left->x - cos(p->angle) / 5) - 0.15)] == '1')
			return (false);
		if (map[(int)((p->top_right->y + sin(p->angle) / 5) - 0.15)]\
		[(int)((p->top_right->x - cos(p->angle) / 5) + 0.15)] == '1')
			return (false);
		if (map[(int)((p->bottom_left->y + sin(p->angle) / 5) + 0.15)]\
		[(int)((p->bottom_left->x - cos(p->angle) / 5) - 0.15)] == '1')
			return (false);
		if (map[(int)((p->bottom_right->y + sin(p->angle) / 5) + 0.15)]\
		[(int)((p->bottom_right->x - cos(p->angle) / 5) + 0.15)] == '1')
			return (false);
	}
	return (true);
}

void	move_player(int keycode, t_data *data)
{
	if (keycode == XK_w && check_hitbox(data->config->map, data->player, true) == true)
		move_up(data);
	else if (keycode == XK_d)
		move_right(data);
	else if (keycode == XK_s && check_hitbox(data->config->map, data->player, false) == true)
		move_down(data);
	else if (keycode == XK_a)
		move_left(data);
	else if (keycode == XK_left)
		turn_left(data);
	else if (keycode == XK_right)
		turn_right(data);
	render_minimap(data);
}

void	move_up(t_data *data)
{
	data->player->coordinate->y -= sin(data->player->angle) / 5;
	data->player->coordinate->x += cos(data->player->angle) / 5;
	init_player_hitbox(data->player);
}

void	move_left(t_data *data)
{

}

void	move_right(t_data *data)
{
	
}

void	move_down(t_data *data)
{
	data->player->coordinate->y += sin(data->player->angle) / 5;
	data->player->coordinate->x -= cos(data->player->angle) / 5;
	init_player_hitbox(data->player);
}

void	turn_left(t_data *data)
{
	data->player->angle += 0.1;
}

void	turn_right(t_data *data)
{
	data->player->angle -= 0.1;
}
