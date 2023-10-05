/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/05 13:01:27 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	raycasting(t_config *config)
{
	t_data	data;
	t_mlx	mlx;

	get_config_address(config);
	get_data_address(&data);
	get_mlx_address(&mlx);
	(void)config;
	// data_init(&data);
	data.config = config;
	data.mlx = &mlx;
	t_mlx_init(&mlx, &data);
	mlx_hook(mlx.mlx_win, 17, 0, &event_close, &mlx);
	mlx_hook(mlx.mlx_win, 2, (1L<<0), &event_move, &mlx);
	mlx_loop_hook(mlx.mlx, &event_key_hook, &data);
	mlx_loop(mlx.mlx);
}
