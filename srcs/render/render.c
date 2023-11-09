// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   render.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/10/03 18:15:02 by tduprez           #+#    #+#             */
// /*   Updated: 2023/10/27 13:30:16 by tduprez          ###   ########lyon.fr   */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/cub3D.h"

void	display_slice(t_data *data, t_slice *slice);
void	display_loops(t_data *data, t_slice *slice);
void	get_tex_x(t_data *data, t_slice *slice);
int		get_text_pix(t_text *text, int x, int y);
// void	render_border(t_data *data);

// void	render(t_config *config)
// {
// 	t_data data;

// 	get_data_address(&data);
// 	init_data(&data, config);
// 	mlx_hook(data.mlx->mlx_win, 17, 0, &event_close, data.mlx);
// 	mlx_hook(data.mlx->mlx_win, 2, (1L << 0), &event_move, data.mlx);
// 	init_image_data(data.mlx, config);
// 	render_minimap(&data);
// 	render_player(data.mlx->player);
// 	dda(&data);
// 	put_window_image_to_window(data.mlx, data.player->coor->x, 
// 	data.player->coor->y);
// 	mlx_loop(data.mlx->mlx);
// 	return;
// }

// void	mlx_clear_image(t_mlx *mlx)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < MAP_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < MAP_WIDTH)
// 		{
// 			put_pixel(mlx->mini_map_border, x, y, 0x00000);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return ;
// }

// void	put_window_image_to_window(t_mlx *m, float x, float y)
// {
// 	(void)y;
// 	(void)x;
// 	(void)m;
// 	mlx_clear_image(m);
// 	ft_put_img_to_img(m->mini_map_border, m->mini_map, 90 - x * 15 , 90 - y * 15);
// 	render_border(get_data_address(NULL));
// 	ft_put_img_to_img(m->mini_map_border, m->player, 100, 100);
// 	ft_put_img_to_img(m->window, m->mini_map_border, 30, 30);
// 	mlx_put_image_to_window(m->mlx, m->mlx_win, m->window->img, 0, 0);
// 	return ;
// }
// void	render_border(t_data *data)
// {
// 	int x;
// 	int y;

// 	y = 0;
// 	while (y < MAP_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < MAP_WIDTH)
// 		{
// 			if (x < 2 || y < 2 || y > MAP_HEIGHT - 2 || x > MAP_WIDTH - 2)
// 				put_pixel(data->mlx->mini_map_border, x, y, 0x8395a7);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return ;
// }


// void render_minimap(t_data *data)
// {
// 	int x;
// 	int y;

// 	y = 0;
// 	while (y < data->config->map_size)
// 	{
// 		x = 0;
// 		while (data->config->map[y][x] && data->config->map[y][x] != '\n')
// 		{
// 			if (data->config->map[y][x] == '1')
// 				put_square(data->mlx, x, y, 0);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return;
// }

// void render_player(t_image *player)
// {
// 	int	x;
// 	int	y;

// 	y = 0;

// 	while (y < 8)
// 	{
// 		x = 0;
// 		while (x < 8)
// 			put_pixel(player, x++, y, 0x00FF0000);
// 		y++;
// 	}
// 	return ;
// }

void	render_floor_ceiling(t_data *data)
{
	int		i;
	int		floor_start;
	int		size;
	char	*dst;

	i = 0;
	floor_start = WIN_W * (WIN_H * 0.5);
	size = data->mlx.window->bpp / 8;
	dst = NULL;
	while (i < WIN_H * WIN_W)
	{ 
		if (i >= 0 && i < floor_start)
		{
			dst = data->mlx.window->img_addr + i * size;
			*(unsigned int *)dst = data->ceiling_color;
		}
		else if (i >= 0 && i > floor_start)
		{
			dst = data->mlx.window->img_addr + i * size;
			*(unsigned int *)dst = data->floor_color;
		}
		i++;
	}
}

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
			continue;
		display_slice(data, &slice);
		slice.i++;
	}
}

void	display_slice(t_data *data, t_slice *slice)
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

void	display_loops(t_data *data, t_slice *slice)
{
	int		x;
	int		y;
	double	step;
	int		color;

	step = slice->text->text_h / slice->slice_h;
	y = slice->tl.y - 1;
	while(++y < slice->br.y)
	{
		if (y < 0)
		{
			slice->tex_y += -y * step;
			y = 0;
		}
		if (y >= WIN_H)
			break;
		if (y >= 0 && y < WIN_H)
		{
			color = get_text_pix(slice->text, slice->tex_x, slice->tex_y);
			// printf("%d\n", slice->tl.x);
			x = slice->tl.x - 1;
			while (++x < slice->br.x)
				put_pixel(data->mlx.window, x, y, color);
		}
		slice->tex_y += step;
	}
}

void	get_tex_x(t_data *d, t_slice *s)
{
	// Calculating exact hit position
	double		perp_angle;
	double		hit_length;
	t_coor_f	wall_x;
	float		cell_pos;

	perp_angle = (PI / 2) - s->ray->angle + get_angle_f(d->player.coor, coor_i_to_f(d->player.view_dst_pos));
	hit_length = s->ray->perp_wall_dist * 0.5 * d->cell_size / sin(perp_angle);
	wall_x = get_coor_f_from_origin(d->player.coor, s->ray->angle, hit_length);
	// Getting hit position relative to the cell
	if (s->ray->hit_side == 1 || s->ray->hit_side == 3) // Horizontal hit
		cell_pos = wall_x.y - (int)(wall_x.y / d->cell_size) * d->cell_size;
	else // Vertical hit
		cell_pos = wall_x.x - (int)(wall_x.x / d->cell_size) * d->cell_size;
	if (s->ray->hit_side == 3 || s->ray->hit_side == 2) // Converting cell_pos to ratio
		cell_pos = cell_pos / d->cell_size;
	else // Flip texture if the side hit is the top or the right side of a cell
		cell_pos = 1.0f - cell_pos / d->cell_size;
	s->tex_x = cell_pos * s->text->text_w; // Mapping ratio to texture dimension
	// printf("texture->width_img %d\n", texture->width_img);
}

int	get_text_pix(t_text *text, int x, int y)
{
	int	color;
	
	if (!text)
		return (0);
	if (x < 0 || x >= text->text_w || y < 0 || y >= text->text_h)
		return (0);
	color = (*(int *)(text->text_adr + (x * text->bits_per_pixel / 8) + (y * text->line_length)));
	return (color);
}

