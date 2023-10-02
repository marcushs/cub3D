/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:37:54 by hleung            #+#    #+#             */
/*   Updated: 2023/10/02 14:29:56 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		trim_empty_lines_after_map(t_config *config);
int		check_map_chars(t_config *config);

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

int	check_map_chars(t_config *config)
{
	int	i;
	int	j;
	int	chars[256];

	i = -1;
	while (++i < 256)
		chars[i] = 0;
	i = -1;
	while (++i < config->map_size)
	{
		j = -1;
		while (config->map[i][++j])
			chars[(int)config->map[i][j]]++;
	}
	if (chars[69] + chars[78] + chars[83] + chars[87] != 1)
		return (ft_putstr(POV_ERR), -1);
	i = -1;
	while (++i < 256)
		if ((i != 10 && i != 32 && i != 48 && i != 49 && i != 69 && \
			i != 78 && i != 83 && i != 87) && chars[i])
			return (ft_putstr(INV_CHAR), -1);
	return (0);
}
