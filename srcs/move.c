/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:48:27 by hleung            #+#    #+#             */
/*   Updated: 2023/10/11 17:29:43 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_up(t_data *data);
void	move_right(t_data *data);
void	move_down(t_data *data);
void	move_left(t_data *data);


float	get_direction_vector_length(t_data *data, bool is_inverse)
{
	float	vector_x = data->mlx->player->coordinate->x;
	float	vector_y = data->mlx->player->coordinate->y;
	float	step_size = 0.05;
	float	res = 0;

	(void)is_inverse;
	while (data->config->map[(int)vector_y] && data->config->map[(int)vector_y][(int)vector_x] != '1')
	{
		if (is_inverse == true)
		{
			vector_x -= cos(data->mlx->player->angle) * step_size;
			vector_y += sin(data->mlx->player->angle) * step_size;
		}
		else
		{
			vector_x += cos(data->mlx->player->angle) * step_size;
			vector_y -= sin(data->mlx->player->angle) * step_size;
		}
		res += 0.05;
	}
	return (res);
}

bool	check_hitbox(t_data *data)
{
	if (!(data->config->map[(int)(data->mlx->player->top_left->y - 0.25)][(int)(data->mlx->player->top_left->x - 0.25)] != '1'))
		return (false);
	if (!(data->config->map[(int)(data->mlx->player->top_right->y - 0.25)][(int)(data->mlx->player->top_right->x + 0.25)] != '1'))
		return (false);
	if (!(data->config->map[(int)(data->mlx->player->bottom_left->y + 0.25)][(int)(data->mlx->player->bottom_left->x - 0.25)] != '1'))
		return (false);
	if (!(data->config->map[(int)(data->mlx->player->bottom_right->y + 0.25)][(int)(data->mlx->player->bottom_right->x + 0.25)] != '1'))
		return (false);
	return (true);
}

void	move_player(int keycode, t_data *data)
{
	if (keycode == XK_w && check_hitbox(data) == true)
		move_up(data);
	else if (keycode == XK_d)
		move_right(data);
	else if (keycode == XK_s && get_direction_vector_length(data, true) > 0.65 && check_hitbox(data) == true)
		move_down(data);
	else if (keycode == XK_a)
		move_left(data);
	render_minimap(data);
}

void	move_up(t_data *data)
{
	data->mlx->player->coordinate->y -= sin(data->mlx->player->angle) / 5;
	data->mlx->player->coordinate->x += cos(data->mlx->player->angle) / 5;
	init_player_hitbox(data->mlx);
}

void	move_right(t_data *data)
{
	data->mlx->player->angle -= 0.1;
}

void	move_down(t_data *data)
{
	data->mlx->player->coordinate->y += sin(data->mlx->player->angle) / 5;
	data->mlx->player->coordinate->x -= cos(data->mlx->player->angle) / 5;
	init_player_hitbox(data->mlx);
}

void	move_left(t_data *data)
{
	data->mlx->player->angle += 0.1;
}
