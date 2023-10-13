/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:10:53 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/13 14:43:00 by tduprez          ###   ########lyon.fr   */
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
		if (!tmp)
			free_config_exit_msg(config, EXIT_FAILURE, MALLOC_ERR);
		free(config->map[y]);
		config->map[y] = tmp;
		y++;
	}
}

void	trim_map_back_spaces(t_config *config)
{
	int		x;
	int		y;
	char	*trim_copy;
	char	*tmp;

	y = 0;
	while (y < config->map_size)
	{
		x = ft_strlen(config->map[y]) - 2;
		while (config->map[y][x] == ' ' && x > 0)
			x--;
		if (x != (int)ft_strlen(config->map[y]) - 2)
		{
			trim_copy = ft_substr(config->map[y], 0, x + 1);
			tmp = ft_strdup(trim_copy);
			free(trim_copy);
			trim_copy = ft_strjoin(tmp, "\n");
			free(tmp);
			if (!trim_copy)
				free_config_exit_msg(config, EXIT_FAILURE, MALLOC_ERR);
			free(config->map[y]);
			config->map[y] = trim_copy;
		}
		y++;
	}
}
