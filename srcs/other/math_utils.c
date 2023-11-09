/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:04:46 by hleung            #+#    #+#             */
/*   Updated: 2023/11/09 09:06:07 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

double	radian_to_degree(double radian)
{
	return (180.0f / PI * radian);
}

double	degree_to_radian(double degree)
{
	return (degree / (180.0f / PI));
}

double	get_angle(t_coor_i start, t_coor_i end)
{
	double	dx;
	double	dy;

	dx = (double)(end.x - start.x);
	dy = (double)(end.y - start.y);
	if (dx >= 0 && dy < 0)
		return (atan(-dy / dx));
	else if (dx < 0 && dy < 0)
		return (atan(dx / dy) + M_PI_2);
	else if (dx < 0 && dy > 0)
		return (atan(-dy / dx) + PI);
	else
		return (atan(dx / dy) + M_PI + M_PI_2);
}

double	get_angle_f(t_coor_f start, t_coor_f end)
{
	double	dx;
	double	dy;

	dx = (double)(end.x - start.x);
	dy = (double)(end.y - start.y);
	if (dx >= 0 && dy < 0)
		return (atan(-dy / dx));
	else if (dx < 0 && dy < 0)
		return (atan(dx / dy) + M_PI_2);
	else if (dx < 0 && dy > 0)
		return (atan(-dy / dx) + PI);
	else
		return (atan(dx / dy) + M_PI + M_PI_2);
}

double	get_coor_f_length(t_coor_f start, t_coor_f end)
{
	double	dx;
	double	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (sqrt(dx * dx + dy * dy));
}
