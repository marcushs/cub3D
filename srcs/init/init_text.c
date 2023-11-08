/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:58:38 by hleung            #+#    #+#             */
/*   Updated: 2023/11/03 08:59:23 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	init_text(t_data *data)
{
	data->textures = malloc(sizeof(t_text) * 4);
	if (!data->textures)
		return (1);
	for (int i = 0; i < 4; i++)
		load_text(data, &data->textures[i], data->text_paths[i]);
	return (0);
}