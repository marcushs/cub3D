/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:58:38 by hleung            #+#    #+#             */
/*   Updated: 2023/11/08 13:16:43 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	get_texture(t_data *data, t_text *text, char *text_path);

void	init_text(t_data *data)
{
	int	i;

	data->textures = malloc(sizeof(t_text) * 4);
	if (!data->textures)
	{
		ft_putstr(MALLOC_ERR);
		free_data(data);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 4)
	{
		if (get_texture(data, &data->textures[i], data->config.text_paths[i]) == -1)
		{
			free_data(data);
			exit(EXIT_FAILURE);
		};
		i++;
	}
}

static int	get_texture(t_data *data, t_text *text, char *text_path)
{
	text->text = mlx_xpm_file_to_image(data->mlx.mlx, text_path, &text->text_w, &text->text_h);
	if (!text->text)
	{
		printf(TEXT_ERR, text_path);
		return (-1);
	}
	text->text_adr = mlx_get_data_addr(text->text, &text->bits_per_pixel, &text->line_length, &text->endian);
	if (!text->text_adr)
		return (-1);
	return (0);
}
