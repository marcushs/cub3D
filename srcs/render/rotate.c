/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:19:40 by hleung            #+#    #+#             */
/*   Updated: 2023/11/09 16:36:21 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	rotate_right(t_data *data)
{
	double	old_dir_x;

	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(data->rot_speed) - \
	data->player.dir.y * sin(data->rot_speed);
	data->player.dir.y = old_dir_x * sin(data->rot_speed) + \
	data->player.dir.y * cos(data->rot_speed);
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;

	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(-data->rot_speed) - \
	data->player.dir.y * sin(-data->rot_speed);
	data->player.dir.y = old_dir_x * sin(-data->rot_speed) + \
	data->player.dir.y * cos(-data->rot_speed);
}
