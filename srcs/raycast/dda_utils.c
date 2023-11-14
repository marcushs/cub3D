/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:00:10 by hleung            #+#    #+#             */
/*   Updated: 2023/11/09 14:43:02 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	set_steps(t_data *data, t_ray *ray, t_dda *dda);

void	set_dda_values(t_data *data, t_ray *ray, t_dda *dda)
{
	dda->map = coor_f_to_i(data->player.coor);
	if (ray->ray_dir.x == 0.0)
		dda->unit_step.x = 1e30;
	else
		dda->unit_step.x = fabs(1.0 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0.0)
		dda->unit_step.y = 1e30;
	else
		dda->unit_step.y = fabs(1.0 / ray->ray_dir.y);
	set_steps(data, ray, dda);
	dda->ray_len = get_coor_i_sq_len(dda->map, dda->map);
}

int	is_in_map(t_data *data, t_coor_i pos)
{
	if (pos.x < 0 || pos.x > data->w_size - 1)
		return (0);
	if (pos.y < 0 || pos.y > data->h_size - 1)
		return (0);
	return (1);
}

static void	set_steps(t_data *data, t_ray *ray, t_dda *dda)
{
	if (ray->ray_dir.x < 0)
	{
		dda->step.x = -1;
		dda->axis_len.x = (data->player.coor.x - dda->map.x) \
		* dda->unit_step.x;
	}
	else
	{
		dda->step.x = 1;
		dda->axis_len.x = (dda->map.x + 1.0 - data->player.coor.x) \
		* dda->unit_step.x;
	}
	if (ray->ray_dir.y < 0)
	{
		dda->step.y = -1;
		dda->axis_len.y = (data->player.coor.y - dda->map.y) \
		* dda->unit_step.y;
	}
	else
	{
		dda->step.y = 1;
		dda->axis_len.y = (dda->map.y + 1.0 - data->player.coor.y) \
		* dda->unit_step.y;
	}
}
