/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:37:54 by hleung            #+#    #+#             */
/*   Updated: 2023/10/13 14:19:54 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3D.h"

int			check_map_chars(t_config *config);

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

void	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0')
			exit(1);
		i++;
	}
}

void	check_open_walls(t_config *config, int x, int y)
{
	if (config->map[y - 1][x] && (config->map[y - 1][x] == ' ' || config->map[y - 1][x] == '\n'))
		free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
	if (config->map[y + 1][x] && (config->map[y + 1][x] == ' ' || config->map[y + 1][x] == '\n'))
		free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
	if (config->map[y][x - 1] && (config->map[y][x - 1] == ' ' || config->map[y][x - 1] == '\n'))
		free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
	if (config->map[y][x + 1] && (config->map[y][x + 1] == ' ' || config->map[y][x + 1] == '\n'))
		free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
	return ;
}

int	check_walls(t_config *config)
{
	int	x;
	int	y;

	y = 1;
	check_line(config->map[0]);
	check_line(config->map[config->map_size - 1]);
	while (y < config->map_size - 2)
	{
		x = 0;
		while (config->map[y][x])
		{
			if (config->map[y][x] == '0')
				check_open_walls(config, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
