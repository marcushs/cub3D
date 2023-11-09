/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:14:10 by hleung            #+#    #+#             */
/*   Updated: 2023/11/09 16:15:29 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	display_slice(t_data *data, t_slice *slice);
static void	display_loops(t_data *data, t_slice *slice);
static void	get_tex_x(t_data *d, t_slice *s);
static int	get_text_pix(t_text *text, int x, int y);

void	render_rays(t_data *data)
{
	t_slice	slice;

	slice.i = 0;
	slice.slice_w = WIN_W / data->ray_nb;
	while (slice.i < data->ray_nb)
	{
		slice.ray = &data->rays[slice.i];
		slice.text = &data->textures[slice.ray->hit_side];
		if (slice.ray->perp_wall_dist == -1)
			continue ;
		display_slice(data, &slice);
		slice.i++;
	}
}

static void	display_slice(t_data *data, t_slice *slice)
{
	slice->slice_h = (float)WIN_H / (float)slice->ray->perp_wall_dist;
	slice->tl.x = slice->i * slice->slice_w;
	slice->tl.y = (WIN_H / 2) - slice->slice_h / 2;
	slice->br.x = slice->i * slice->slice_w + slice->slice_w;
	slice->br.y = (WIN_H / 2) + slice->slice_h / 2;
	slice->tex_y = 0;
	get_tex_x(data, slice);
	display_loops(data, slice);
}

static void	display_loops(t_data *data, t_slice *slice)
{
	int		x;
	int		y;
	double	step;
	int		color;

	step = slice->text->text_h / slice->slice_h;
	y = slice->tl.y - 1;
	while (++y < slice->br.y)
	{
		if (y < 0)
		{
			slice->tex_y += -y * step;
			y = 0;
		}
		if (y >= WIN_H)
			break ;
		if (y >= 0 && y < WIN_H)
		{
			color = get_text_pix(slice->text, slice->tex_x, slice->tex_y);
			x = slice->tl.x - 1;
			while (++x < slice->br.x)
				put_pixel(data->mlx.window, x, y, color);
		}
		slice->tex_y += step;
	}
}

static void	get_tex_x(t_data *d, t_slice *s)
{
	double		perp_angle;
	double		hit_length;
	t_coor_f	wall_x;
	float		cell_pos;

	perp_angle = (PI / 2) - s->ray->angle + \
	get_angle_f(d->player.coor, coor_i_to_f(d->player.view_dst_pos));
	hit_length = s->ray->perp_wall_dist * 0.5 * d->cell_size / sin(perp_angle);
	wall_x = get_coor_f_from_origin(d->player.coor, s->ray->angle, hit_length);
	if (s->ray->hit_side == 1 || s->ray->hit_side == 3)
		cell_pos = wall_x.y - (int)(wall_x.y / d->cell_size) * d->cell_size;
	else
		cell_pos = wall_x.x - (int)(wall_x.x / d->cell_size) * d->cell_size;
	if (s->ray->hit_side == 3 || s->ray->hit_side == 2)
		cell_pos = cell_pos / d->cell_size;
	else
		cell_pos = 1.0 - cell_pos / d->cell_size;
	s->tex_x = cell_pos * s->text->text_w;
}

static int	get_text_pix(t_text *text, int x, int y)
{
	int	color;

	if (!text)
		return (0);
	if (x < 0 || x >= text->text_w || y < 0 || y >= text->text_h)
		return (0);
	color = (*(int *)(text->text_adr + \
	(x * text->bits_per_pixel / 8) + (y * text->line_length)));
	return (color);
}
