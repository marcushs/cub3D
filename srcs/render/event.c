/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:44 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/09 16:49:12 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	update(t_data *data)
{
	keyboard_input(data);
	render_floor_ceiling(data);
	raycast(data);
	render_rays(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
	data->mlx.window->img, 0, 0);
	return (0);
}

int	exit_prog(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx, data->mlx.window->img);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_destroy_display(data->mlx.mlx);
	free_data(data);
	printf("Cub3D Closed!\n");
	exit(EXIT_SUCCESS);
	return (0);
}

void	keyboard_input(t_data *data)
{
	if (data->keyboard[XK_W])
		move_forward(data);
	if (data->keyboard[XK_S])
		move_backward(data);
	if (data->keyboard[XK_A])
		move_left(data);
	if (data->keyboard[XK_D])
		move_right(data);
	if (data->keyboard[XK_LEFT])
		rotate_left(data);
	if (data->keyboard[XK_RIGHT])
		rotate_right(data);
	if (data->keyboard[XK_ESC])
		exit_prog(data);
	data->player.view_dst_pos.x = data->player.dir.x * \
	data->view_dst + data->player.coor.x;
	data->player.view_dst_pos.y = data->player.dir.y * \
	data->view_dst + data->player.coor.y;
}
