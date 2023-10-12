/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:10:53 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/12 16:12:18 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	trim_map_first_spaces(t_config *config)
{
	int		x;
	int		y;
	int		nb_spaces;
	char	*tmp;

	nb_spaces = INT_MAX;
	y = 0;
	while (y < config->map_size)
	{
		x = 0;
		while (config->map[y][x] && config->map[y][x] == ' ')
			x++;
		if (x < nb_spaces)
			nb_spaces = x;
		y++;
	}
	y = 0;
	while (y < config->map_size)
	{
		tmp = ft_substr(config->map[y], nb_spaces, ft_strlen(config->map[y]));
		free(config->map[y]);
		config->map[y] = tmp;
		y++;
	}
}

void	trim_map_back_spaces(t_config *config)
{
	int		x;
	int		y;
	char	*tmp;

	y = 0;
	while (y < config->map_size)
	{
		x = ft_strlen(config->map[y]) - 2;
		while (config->map[y][x] == ' ' && x > 0)
			x--;
		if (x != (int)ft_strlen(config->map[y]) - 2)
		{
			tmp = ft_substr(config->map[y], 0, x + 1);
			tmp = ft_strjoin(tmp, "\n");
			free(config->map[y]);
			config->map[y] = tmp;
		}
		y++;
	}
}
