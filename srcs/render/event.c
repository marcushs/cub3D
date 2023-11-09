/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:44 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/09 14:39:38 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int update(t_data *data);

// int	event_move(int keycode, t_mlx* mlx)
// {
// 	(void)mlx;
// 	if (keycode == 65307)
// 	{
// 		mlx_destroy_image(mlx->mlx, mlx->mini_map->img);
// 		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
// 		mlx_destroy_display(mlx->mlx);
// 		free(mlx->mlx);
// 		free_config_exit_msg(get_config_address(NULL), 
// 		EXIT_FAILURE, "Cub3D closed !\n");
// 	}
// 	// else
// 	// 	move_player(keycode, get_data_address(NULL));
// 	return (1);
// }

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
	if (data->keyboard[XK_w])
		move_forward(data);
	if (data->keyboard[XK_s])
		move_backward(data);
	if (data->keyboard[XK_a])
		move_left(data);
	if (data->keyboard[XK_d])
		move_right(data);
	if (data->keyboard[XK_left])
		rotate_left(data);
	if (data->keyboard[XK_right])
		rotate_right(data);
	if (data->keyboard[XK_esc])
		exit_prog(data);
	data->player.view_dst_pos.x = data->player.dir.x * data->view_dst + data->player.coor.x;
	data->player.view_dst_pos.y = data->player.dir.y * data->view_dst + data->player.coor.y;
}

int	key_press(int keycode, t_data *data)
{
	keycode = keycode % 200; 
	if (keycode < 200)
		data->keyboard[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	keycode = keycode % 200;
	if (keycode < 200)
		data->keyboard[keycode] = 0;
	return(0);
}

int	hooks_and_loops(t_data *data)
{
	mlx_hook(data->mlx.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx.mlx_win, 17, 0, exit_prog, data);
	mlx_loop_hook(data->mlx.mlx, update, data);
	mlx_loop(data->mlx.mlx);
	return (0);
}

int update(t_data *data)
{
	keyboard_input(data);
	render_floor_ceiling(data);
	raycast(data);
	// for (int i = 0; i < data->ray_nb; i++)
	// 	printf("data->ray[%d]->perp_wall_dist = %f\n", i, data->rays[i].perp_wall_dist);
	render_rays(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, data->mlx.window->img, 0, 0);
	return (0);
}
