/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:58:01 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/09 16:40:18 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

void	set_map_null(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->map_size)
		config->map[i++] = NULL;
	return ;
}

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

void	trim_map_first_spaces(t_config *config)
{
	int		x;
	int		y;
	int		nb_spaces;
	char	*tmp;

	nb_spaces = INT_MAX;
	y = -1;
	while (++y < config->map_size)
	{
		x = 0;
		while (config->map[y][x] && config->map[y][x] == ' ')
			x++;
		if (x < nb_spaces)
			nb_spaces = x;
	}
	y = 0;
	while (y < config->map_size)
	{
		tmp = ft_substr(config->map[y], nb_spaces, ft_strlen(config->map[y]));
		if (!tmp)
			free_config_exit_msg(config, EXIT_FAILURE, MALLOC_ERR);
		free(config->map[y]);
		config->map[y++] = tmp;
	}
	return ;
}

void	trim_map_back_spaces(t_config *config)
{
	int		x;
	int		y;
	char	*trim_copy;
	char	*tmp;

	y = -1;
	while (++y < config->map_size)
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
	}
	return ;
}
