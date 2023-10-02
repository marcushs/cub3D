/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:37:54 by hleung            #+#    #+#             */
/*   Updated: 2023/10/02 10:36:50 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	trim_empty_lines_after_map(t_config *config)
{
	int		i;
	int		to_trim;

	i = 0;
	to_trim = 0;
	while (i < config->map_size && !is_empty_line(config->map[i]))
		i++;
	to_trim = i;
	while (i < config->map_size && is_empty_line(config->map[i]))
		i++;
	if (i < config->map_size && !is_empty_line(config->map[i]))
		return (ft_putstr(MAP_EMPTY), -1);
	i = to_trim;
	while (to_trim < config->map_size)
	{
		free_set_null(&config->map[to_trim]);
		to_trim++;
	}
	config->map_size = i;
	return (0);
}
