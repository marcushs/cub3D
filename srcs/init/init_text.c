/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:58:38 by hleung            #+#    #+#             */
/*   Updated: 2023/11/14 12:18:23 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	get_texture(t_data *data, t_text *text, char *text_path, int i);
static int	rgb_to_int(int r, int g, int b);
void		free_textures(t_data *data, int i);

void	init_text(t_data *data)
{
	int	i;

	data->textures = malloc(sizeof(t_text) * 4);
	if (!data->textures)
	{
		ft_putstr(MALLOC_ERR);
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
		mlx_destroy_display(data->mlx.mlx);
		free_data(data);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 4)
	{
		if (get_texture(data, &data->textures[i], \
		data->config.text_paths[i], i) == -1)
		{
			mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
			mlx_destroy_display(data->mlx.mlx);
			free_data(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static int	get_texture(t_data *data, t_text *text, char *text_path, int i)
{
	text->text = mlx_xpm_file_to_image(data->mlx.mlx, text_path, \
	&text->text_w, &text->text_h);
	if (!text->text)
	{
		printf(TEXT_ERR, text_path);
		free_textures(data, i);
		return (-1);
	}
	text->text_adr = mlx_get_data_addr(text->text, &text->bits_per_pixel, \
	&text->line_length, &text->endian);
	if (!text->text_adr)
		return (-1);
	data->floor_color = rgb_to_int(data->config.floor_rgb[0], \
	data->config.floor_rgb[1], data->config.floor_rgb[2]);
	data->ceiling_color = rgb_to_int(data->config.ceiling_rgb[0], \
	data->config.ceiling_rgb[1], data->config.ceiling_rgb[2]);
	return (0);
}

static int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	free_textures(t_data *data, int i)
{
	while (i >= 0)
	{
		if (data->textures[i].text)
			mlx_destroy_image(data->mlx.mlx, data->textures[i].text);
		i--;
	}
}
