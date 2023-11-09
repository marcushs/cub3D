/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:06:58 by hleung            #+#    #+#             */
/*   Updated: 2023/11/09 14:33:46 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static t_coor_f	dda_loop(t_data *data, t_ray *ray, t_dda *dda);
static void	increment_side(t_data *data, t_dda *dda);
static void	hit_wall_ori(t_ray *ray, t_dda *dda);
static t_coor_f make_coor_f(float x, float y);

t_coor_f	dda(t_data *data, t_ray *ray)
{
	t_dda		dda;
	t_coor_f	ret;

	ray->ray_dir = ray->hitpoint;
	ray->ray_dir.x = ray->ray_dir.x - data->player.coor.x;
	ray->ray_dir.y = ray->ray_dir.y - data->player.coor.y;
	set_dda_values(data, ray, &dda);
	ret = dda_loop(data, ray, &dda);
	return (ret);
}

static t_coor_f	dda_loop(t_data *data, t_ray *ray, t_dda *dda)
{
	int	cs;

	cs = data->cell_size;
	while (dda->ray_len < data->view_dst * data->view_dst)
	{
		increment_side(data, dda);
		if (!is_in_map(data, dda->map))
			continue;
		if (data->config.map[dda->map.y / cs][dda->map.x / cs] == '1')
		{
			if (dda->side_hit.y == 0)
				ray->perp_wall_dist = (dda->axis_len.x - dda->unit_step.x) * cs;
			else
				ray->perp_wall_dist = (dda->axis_len.y - dda->unit_step.y) * cs;
			hit_wall_ori(ray, dda);
			ray->cell.x = dda->map.x / cs;
			ray->cell.y = dda->map.y / cs;
			return (coor_i_to_f(dda->map));
		}
	}
	return (make_coor_f(-1, -1));
}

static void	increment_side(t_data *data, t_dda *dda)
{
	if (dda->axis_len.x < dda->axis_len.y)
	{
		dda->axis_len.x += dda->unit_step.x;
		dda->map.x += dda->step.x;
		dda->side_hit.x = dda->step.x;
		dda->side_hit.y = 0;
	}
	else
	{
		dda->axis_len.y += dda->unit_step.y;
		dda->map.y += dda->step.y;
		dda->side_hit.y = dda->step.y;
		dda->side_hit.x = 0;
	}
	dda->ray_len = get_coor_i_sq_len(coor_f_to_i(data->player.coor), dda->map);
}

static void	hit_wall_ori(t_ray *ray, t_dda *dda)
{
	if (dda->side_hit.x == 1) 
		ray->hit_side = 3; // west wall
	else if (dda->side_hit.x == -1)
		ray->hit_side = 1; // east wall
	else if (dda->side_hit.y == 1)
		ray->hit_side = 0; // north wall
	else
		ray->hit_side = 2; // south wall
}

static t_coor_f make_coor_f(float x, float y)
{
	t_coor_f	coor;

	coor.x = x;
	coor.y = y;
	return (coor);
}
