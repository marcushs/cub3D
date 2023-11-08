/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:44 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/08 15:21:01 by hleung           ###   ########.fr       */
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

// int	event_close(t_mlx *mlx)
// {
// 	(void)mlx;
// 	mlx_destroy_image(mlx->mlx, mlx->mini_map->img);
// 	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
// 	mlx_destroy_display(mlx->mlx);
// 	free(mlx->mlx);
// 	free_config_exit_msg(get_config_address(NULL),
// 	EXIT_FAILURE, "Cub3D closed !\n");
// 	return (EXIT_FAILURE);
// }
void	keyboard_input(t_data *data)
{
	if (data->keyboard[XK_w])
		// move_forward(data);
		printf("w pressed\n");
	if (data->keyboard[XK_s])
		// move_backward(data);
		printf("s pressed\n");
	if (data->keyboard[XK_a])
		// move_left(data);
		printf("a pressed\n");
	if (data->keyboard[XK_d])
		// move_right(data);
		printf("d pressed\n");
	if (data->keyboard[XK_left])
		// rotate_left(data);
		printf("left pressed\n");
	if (data->keyboard[XK_right])
		// rotate_right(data);
		printf("right pressed\n");
	if (data->keyboard[XK_esc])
		// exit_prog(data);
		printf("esc pressed\n");
	// data->player.view_dst_pos.x = data->player.dir.x * data->view_dst + data->player.coordinate.x;
	// data->player.view_dst_pos.y = data->player.dir.y * data->view_dst + data->player.coordinate.y;
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
	mlx_loop_hook(data->mlx.mlx, update, data);
	mlx_loop(data->mlx.mlx);
	return (0);
}

int update(t_data *data)
{
	keyboard_input(data);
	render_floor_ceiling(data);
	// set_grid_cell(data, data->mouse_pos.x, data->mouse_pos.y);
	// print_grid(data);
	// t_coor_f hit = dda(data, data->rays);
	// bresenham(data, coor_f_to_i(data->player.coordinate), coor_f_to_i(hit), WHITE);
	// bresenham(data, coor_f_to_i(data->player.coordinate), data->player.view_dst_pos, WHITE);
	// draw_circle_color(data, coor_f_to_i(hit), GREEN);
	// create_rays(data);
	// calculate_collision(data);
	// rays_render(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, data->mlx.window->img, 0, 0);
	return (0);
}
