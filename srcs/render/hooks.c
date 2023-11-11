/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:26:40 by hleung            #+#    #+#             */
/*   Updated: 2023/11/11 07:59:21 by hleung           ###   ########.fr       */
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
	keycode = keycode % 200;
	if (keycode < 200)
		data->keyboard[keycode] = 1;
	return (0);
}

static int	key_release(int keycode, t_data *data)
{
	keycode = keycode % 200;
	if (keycode < 200)
		data->keyboard[keycode] = 0;
	return (0);
}
