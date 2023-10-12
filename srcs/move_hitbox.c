/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hitbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:43:16 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/12 20:45:59 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	change_hitbox_moves(t_hitbox_tmp *moves, t_player *p, int direction);

bool check_hitbox(char **map, t_player *p, int direction)
{
	t_hitbox_tmp	mv;

	mv.x = 0.0;
	mv.y = 0.0;
	change_hitbox_moves(&mv, p, direction);
	if (map[(int)(p->t_left->y + mv.y)][(int)(p->t_left->x + mv.x)] == '1')
		return (false);
	if (map[(int)(p->t_right->y + mv.y)][(int)(p->t_right->x + mv.x)] == '1')
		return (false);
	if (map[(int)(p->b_left->y + mv.y)][(int)(p->b_left->x + mv.x)] == '1')
		return (false);
	if (map[(int)(p->b_right->y + mv.y)][(int)(p->b_right->x + mv.x)] == '1')
		return (false);
	return true;
}

static void	change_hitbox_moves(t_hitbox_tmp *moves, t_player *p, int direction)
{
	if (direction == XK_w)
	{
		moves->x = cos(p->angle) / 5;
		moves->y -= sin(p->angle) / 5;
	}
	else if (direction == XK_s)
	{
		moves->x -= cos(p->angle) / 5;
		moves->y = sin(p->angle) / 5;
	}
	else if (direction == XK_a)
	{
		moves->x -= sin(p->angle) / 5;
		moves->y -= cos(p->angle) / 5;
	}
	else if (direction == XK_d)
	{
		moves->x = sin(p->angle) / 5;
		moves->y = cos(p->angle) / 5;
	}
	return ;
}
