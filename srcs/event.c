/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:44 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/05 17:48:20 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	event_key_hook(int keycode, t_data *data)
{
	(void)keycode;
	(void)data;
	//printf("Hello from key_hook!\n");
	return (0);
}

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
	// else
	// 	move_player(keycode);
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

