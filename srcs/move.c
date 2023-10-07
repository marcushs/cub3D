/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:48:27 by hleung            #+#    #+#             */
/*   Updated: 2023/10/06 11:49:18 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_player(int keycode, t_data *data)
{
	if (keycode == XK_w)
		move_up(data);
	else if (keycode == XK_d)
		move_right(data);
	else if (keycode == XK_s)
		move_down(data);
	else if (keycode == XK_a)
		move_left(data);
}

void	move_up(t_data *data)
{
	// slg->map->map[slg->p->y][slg->p->x] = '0';
	// render_other(*slg, '0');
	// if (slg->map->map[slg->p->y - 1][slg->p->x] == 'C')
	// {
	// 	slg->p->y--;
	// 	render_other(*slg, '0');
	// 	slg->count++;
	// 	slg->steps++;
	// 	ft_printf("Number of steps: %d\n", slg->steps);
	// 	if (slg->count == slg->map->c[67])
	// 		render_temple(*slg);
	// 	slg->map->map[slg->p->y][slg->p->x] = 'P';
	// 	render_other(*slg, 'P');
	// 	return ;
	// }
	// slg->p->y--;
	// slg->steps++;
	// slg->map->map[slg->p->y][slg->p->x] = 'P';
	// ft_printf("Number of steps: %d\n", slg->steps);
	// render_other(*slg, 'P');
	put_player(data->mlx, )
}

void	move_right(t_slg *slg)
{
	slg->map->map[slg->p->y][slg->p->x] = '0';
	render_other(*slg, '0');
	if (slg->map->map[slg->p->y][slg->p->x + 1] == 'C')
	{
		slg->p->x++;
		render_other(*slg, '0');
		slg->count++;
		slg->steps++;
		ft_printf("Number of steps: %d\n", slg->steps);
		if (slg->count == slg->map->c[67])
			render_temple(*slg);
		slg->map->map[slg->p->y][slg->p->x] = 'P';
		render_other(*slg, 'P');
		return ;
	}
	slg->p->x++;
	slg->steps++;
	slg->map->map[slg->p->y][slg->p->x] = 'P';
	ft_printf("Number of steps: %d\n", slg->steps);
	render_other(*slg, 'P');
}

void	move_down(t_slg *slg)
{
	slg->map->map[slg->p->y][slg->p->x] = '0';
	render_other(*slg, '0');
	if (slg->map->map[slg->p->y + 1][slg->p->x] == 'C')
	{
		slg->p->y++;
		render_other(*slg, '0');
		slg->count++;
		slg->steps++;
		ft_printf("Number of steps: %d\n", slg->steps);
		if (slg->count == slg->map->c[67])
			render_temple(*slg);
		slg->map->map[slg->p->y][slg->p->x] = 'P';
		render_other(*slg, 'P');
		return ;
	}
	slg->p->y++;
	slg->steps++;
	slg->map->map[slg->p->y][slg->p->x] = 'P';
	ft_printf("Number of steps: %d\n", slg->steps);
	render_other(*slg, 'P');
}

void	move_left(t_slg *slg)
{
	slg->map->map[slg->p->y][slg->p->x] = '0';
	render_other(*slg, '0');
	if (slg->map->map[slg->p->y][slg->p->x - 1] == 'C')
	{
		slg->p->x--;
		render_other(*slg, '0');
		slg->count++;
		slg->steps++;
		ft_printf("Number of steps: %d\n", slg->steps);
		if (slg->count == slg->map->c[67])
			render_temple(*slg);
		slg->map->map[slg->p->y][slg->p->x] = 'P';
		render_other(*slg, 'P');
		return ;
	}
	slg->p->x--;
	slg->steps++;
	slg->map->map[slg->p->y][slg->p->x] = 'P';
	ft_printf("Number of steps: %d\n", slg->steps);
	render_other(*slg, 'P');
}
