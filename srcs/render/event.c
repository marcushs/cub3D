/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:44 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/19 23:33:54 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	event_move(int keycode, t_mlx* mlx)
{
	(void)mlx;
	if (keycode == 65307)
	{
		mlx_destroy_image(mlx->mlx, mlx->mini_map->img);
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		free_config_exit_msg(get_config_address(NULL), \
		EXIT_FAILURE, "Cub3D closed !\n");
	}
	else
		move_player(keycode, get_data_address(NULL));
	return (1);
}

int	event_close(t_mlx *mlx)
{
	(void)mlx;
	mlx_destroy_image(mlx->mlx, mlx->mini_map->img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_config_exit_msg(get_config_address(NULL), \
	EXIT_FAILURE, "Cub3D closed !\n");
	return (EXIT_FAILURE);
}

