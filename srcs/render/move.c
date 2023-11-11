/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:48:27 by hleung            #+#    #+#             */
/*   Updated: 2023/11/11 17:16:18 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_walkable(t_data *data, float x, float y);

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
	new_dir.x = data->player.dir.x * cos(-PI / 2) - \
	data->player.dir.y * sin(-PI / 2);
	new_dir.y = data->player.dir.x * sin(-PI / 2) + \
	data->player.dir.y * cos(-PI / 2);
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
	new_dir.x = data->player.dir.x * cos(PI / 2) - \
	data->player.dir.y * sin(PI / 2);
	new_dir.y = data->player.dir.x * sin(PI / 2) + \
	data->player.dir.y * cos(PI / 2);
	tmp_coor.x = new_dir.x * data->move_speed + p_pos->x;
	tmp_coor.y = new_dir.y * data->move_speed + p_pos->y;
	if (is_walkable(data, tmp_coor.x, p_pos->y))
		p_pos->x = tmp_coor.x;
	if (is_walkable(data, p_pos->x, tmp_coor.y))
		p_pos->y = tmp_coor.y;
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
