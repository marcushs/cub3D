/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:26:40 by hleung            #+#    #+#             */
/*   Updated: 2023/11/12 07:06:59 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	key_press(int keycode, t_data *data);
static int	key_release(int keycode, t_data *data);

int	hooks_and_loops(t_data *data)
{
	mlx_hook(data->mlx.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx.mlx_win, 17, 0, exit_prog, data);
	mlx_loop_hook(data->mlx.mlx, update, data);
	mlx_loop(data->mlx.mlx);
	return (0);
}

static int	key_press(int keycode, t_data *data)
{	
	if (keycode == XK_ESC)
		exit_prog(data);
	if (keycode == XK_W)
		data->keyboard[FOR] = 1;
	if (keycode == XK_A)
		data->keyboard[LEFT] = 1;
	if (keycode == XK_S)
		data->keyboard[BACK] = 1;
	if (keycode == XK_D)
		data->keyboard[RIGHT] = 1;
	if (keycode == XK_LEFT)
		data->keyboard[A_CLOCK] = 1;
	if (keycode == XK_RIGHT)
		data->keyboard[CLOCK] = 1;
	return (0);
}

static int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_ESC)
		exit_prog(data);
	if (keycode == XK_W)
		data->keyboard[FOR] = 0;
	if (keycode == XK_A)
		data->keyboard[LEFT] = 0;
	if (keycode == XK_S)
		data->keyboard[BACK] = 0;
	if (keycode == XK_D)
		data->keyboard[RIGHT] = 0;
	if (keycode == XK_LEFT)
		data->keyboard[A_CLOCK] = 0;
	if (keycode == XK_RIGHT)
		data->keyboard[CLOCK] = 0;
	return (0);
}
