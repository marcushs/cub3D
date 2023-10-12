/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:37:54 by hleung            #+#    #+#             */
/*   Updated: 2023/10/12 16:10:35 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int			check_map_chars(t_config *config);
void		check_map_walls(t_config *config);
static bool	check_walls(char *map_line, char *line_tmp);
static bool	is_valid_line(char *line);

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

void	check_map_walls(t_config *config)
{
	int		x;
	int		y;
	char	*line_tmp;

	x = -1;
	y = 1;
	trim_map_first_spaces(config);
	trim_map_back_spaces(config);
	line_tmp = config->map[0];
	while (config->map[0][++x] && config->map[0][x] != '\n')
		if (config->map[0][x] != ' ' && config->map[0][x] != '1')
			free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
	while (y < config->map_size)
	{
		if (is_valid_line(config->map[y]) == false)
			free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
		if (check_walls(config->map[y], line_tmp) == false)
			free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
		line_tmp = config->map[y];
		y++;
	}
	return ;
}

static bool	check_walls(char *map_line, char *line_tmp)
{
	int	x;

	x = 0;
	while (map_line[x] && map_line[x] != '\n' && line_tmp[x])
	{
		if (line_tmp[x] == ' ' && (map_line[x] != '1' && map_line[x] != ' '))
			return (false);
		else if (line_tmp[x] != ' ' && line_tmp[x] != '1' && map_line[x] == ' ')
			return (false);
		else if (map_line[x] == ' ' && ((x > 0 && map_line[x - 1] == '0') || \
		(x < (int)ft_strlen(map_line) && map_line[x + 1] == '0')))
			return (false);
		else if (map_line[x] == ' ' && line_tmp[x] == '1' && \
		((x > 0 && line_tmp[x - 1] != '1' && map_line[x - 1] != ' ') || \
		(x < (int)ft_strlen(line_tmp) && line_tmp[x + 1] != '1' && \
		map_line[x + 1] != ' ')))
			return (false);
		else if (map_line[x] == '0' && ((x > 0 && line_tmp[x - 1] == ' ' && \
		map_line[x - 1] != ' ') || (x < (int)ft_strlen(line_tmp) && \
		line_tmp[x + 1] == ' ' && map_line[x + 1] != ' ')))
			return (false);
		x++;
	}
	return (true);
}

static bool	is_valid_line(char *line)
{
	int	x;

	x = 0;
	while (line[x] && line[x] == ' ')
		x++;
	if (line[x] != '1' || line[ft_strlen(line) - 2] != '1')
		return (false);
	return (true);
}
