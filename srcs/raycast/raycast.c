/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 07:29:11 by hleung            #+#    #+#             */
/*   Updated: 2023/11/09 10:56:12 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	make_rays(t_data *data);
void	fill_rays_arr(t_data *data, t_coor_f opp_pos[2]);
void	calculate_collision(t_data *data);

void	raycast(t_data *data)
{
	make_rays(data);
	calculate_collision(data);
}

void	make_rays(t_data *data)
{
	t_coor_i	origin;
	int			opp_len;
	t_coor_f	opp_pos[2];

	origin = coor_f_to_i(data->player.coor);
	opp_len = tan(degree_to_radian(data->fov / 2)) * data->view_dst;
	data->player.angle = get_angle(origin, data->player.view_dst_pos);
	opp_pos[0] = get_coor_f_from_origin(coor_i_to_f(data->player.view_dst_pos) \
	, data->player.angle + M_PI_2, opp_len);
	opp_pos[1] = get_coor_f_from_origin(coor_i_to_f(data->player.view_dst_pos) \
	, data->player.angle - M_PI_2, opp_len);
	fill_rays_arr(data, opp_pos);
}

void	fill_rays_arr(t_data *data, t_coor_f opp_pos[2])
{
	double		inc;
	int			i;
	t_coor_f	r_coor;

	inc = 1.0 / (data->ray_nb - 1.0);
	i = 0;
	while (i < data->ray_nb)
	{
		r_coor = coor_f_interpolation(opp_pos[0], opp_pos[1], inc * i);
		data->rays[i].angle = get_angle_f(data->player.coor, r_coor);
		data->rays[i].hitpoint = r_coor;
		i++;
	}
}

void	calculate_collision(t_data *data)
{
	t_coor_f	hit;
	int			i;

	i = 0;
	while (i < data->ray_nb)
	{
		hit = dda(data, &data->rays[i]);
		if (hit.x != -1 && hit.y != -1)
		{
			data->rays[i].hitpoint = hit;
			data->rays[i].length = get_coor_f_length(data->player.coor, hit);
		}
		else
			data->rays[i].perp_wall_dist = -1; // if no collision, directly put perp_wall_dist to -1
		i++;
	}
}
