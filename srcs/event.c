/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:44 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/05 18:05:15 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	event_key_hook(int keycode, t_data *data)
{
	(void)keycode;
	(void)data;
	// printf("Hello from key_hook!\n");
	return (0);
}

int	map2[10][10] =
				{
					{ 1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,1,0,0,0,0,0,0,1 },
					{ 1,0,1,0,0,1,1,1,1,1 },
					{ 1,0,0,0,0,1,0,0,0,1 },
					{ 1,1,0,0,0,1,1,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,1 },
					{ 1,1,1,1,1,1,1,1,1,1 },
				};

int	event_move(int keycode, t_mlx* mlx)
{
	(void)mlx;
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		free_config_exit_msg(get_config_address(NULL), \
		EXIT_FAILURE, "Cub3D closed !\n");
	}
	else if (keycode == 97 && map2[get_player_address(NULL)->pos_y / 192][(get_player_address(NULL)->pos_x - 10) / 192] != 1)
		get_player_address(NULL)->pos_x -= 10;
	else if (keycode == 119 && map2[(get_player_address(NULL)->pos_y - 10) / 192][get_player_address(NULL)->pos_x / 192] != 1)
		get_player_address(NULL)->pos_y -= 10;
	else if (keycode == 100 && map2[get_player_address(NULL)->pos_y / 192][(get_player_address(NULL)->pos_x + 10) / 192] != 1)
		get_player_address(NULL)->pos_x += 10;
	else if (keycode == 115 && map2[(get_player_address(NULL)->pos_y + 10) / 192][get_player_address(NULL)->pos_x / 192] != 1)
		get_player_address(NULL)->pos_y += 10;
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, 1920, 1920);
	// draw_background(mlx);
	draw_map(mlx);
	draw_square(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	return (1);
}

int	event_close(t_mlx *mlx)
{
	(void)mlx;
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_config_exit_msg(get_config_address(NULL), \
	EXIT_FAILURE, "Cub3D closed !\n");
	return (EXIT_FAILURE);
}

