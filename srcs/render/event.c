/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:44 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/12 07:08:24 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	update(t_data *data)
{
	keyboard_input(data);
	render_minimap(data);
	render_floor_ceiling(data);
	render_player(data->mlx.player);
	raycast(data);
	render_rays(data);
	put_window_image_to_window(data, data->player.coor.x * 0.375, \
	data->player.coor.y * 0.375);
	return (0);
}

int	exit_prog(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx.mlx, data->textures[i].text);
	mlx_destroy_image(data->mlx.mlx, data->mlx.mmb->img);
	mlx_destroy_image(data->mlx.mlx, data->mlx.mini_map->img);
	mlx_destroy_image(data->mlx.mlx, data->mlx.player->img);
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
	if (data->keyboard[FOR])
		move_forward(data);
	if (data->keyboard[BACK])
		move_backward(data);
	if (data->keyboard[LEFT])
		move_left(data);
	if (data->keyboard[RIGHT])
		move_right(data);
	if (data->keyboard[A_CLOCK])
		rotate_left(data);
	if (data->keyboard[CLOCK])
		rotate_right(data);
	data->player.view_dst_pos.x = data->player.dir.x * \
	data->view_dst + data->player.coor.x;
	data->player.view_dst_pos.y = data->player.dir.y * \
	data->view_dst + data->player.coor.y;
}
