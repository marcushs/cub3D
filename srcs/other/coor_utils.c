/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coor_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 07:40:28 by hleung            #+#    #+#             */
/*   Updated: 2023/11/09 08:09:25 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_coor_i	coor_f_to_i(t_coor_f coor_f)
{
	t_coor_i	coor_i;

	coor_i.x = coor_f.x;
	coor_i.y = coor_f.y;
	return (coor_i);
}

t_coor_f	coor_i_to_f(t_coor_i coor_i)
{
	t_coor_f	coor_f;

	coor_f.x = coor_i.x;
	coor_f.y = coor_i.y;
	return (coor_f);
}

/*	The 2 functions below allow us to get coordinates from the origin (player's position), in int or in float
	It gives us a direction (in radian) and a fixed length (in pixels) */

t_coor_i	get_coor_i_from_origin(t_coor_i origin, double radian, double length)
{
	t_coor_i	coor;

	coor.x = cos(-radian) * length + origin.x;
	coor.y = sin(-radian) * length + origin.y;
	return (coor);
}

t_coor_f	get_coor_f_from_origin(t_coor_f origin, double radian, double length)
{
	t_coor_f	coor;

	coor.x = cos(-radian) * length + origin.x;
	coor.y = sin(-radian) * length + origin.y;
	return (coor);
}

t_coor_f	coor_f_interpolation(t_coor_f start, t_coor_f end, float ratio)
{
	t_coor_f	coor;
	float		dx;
	float		dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	coor.x = start.x + dx * ratio;
	coor.y = start.y + dy * ratio;
	return (coor);
}
