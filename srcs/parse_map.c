/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:58:58 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/02 15:33:41 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static bool	is_valid_line(char *line);
static bool	check_walls(char *map_line, char *line_tmp);

void	parse_map(t_config *config)
{
	int		x;
	int		y;
	char	*line_tmp;

	x = -1;
	y = 1;
	line_tmp = config->map[0];
	while (config->map[0][++x] && config->map[0][x] != '\n')
		if (config->map[0][x] != ' ' && config->map[0][x] != '1')
			free_config_exit(config, EXIT_FAILURE);
	while (y < config->map_size)
	{
		if (is_valid_line(config->map[y]) == false)
			free_config_exit(config, EXIT_FAILURE);
		if (check_walls(config->map[y], line_tmp) == false)
			free_config_exit(config, EXIT_FAILURE);
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
		else if (map_line[x] == ' ' && line_tmp[x] == '1' && ((x > 0 && line_tmp[x - 1] != '1' && map_line[x - 1] != ' ') || (x < (int)ft_strlen(line_tmp) && line_tmp[x + 1] != '1' && map_line[x + 1] != ' ')))
			return (printf("TSET\n"), false);
		else if (map_line[x] == '0' && ((x > 0 && line_tmp[x - 1] == ' ' && map_line[x - 1] != ' ') || \
		(x < (int)ft_strlen(line_tmp) && line_tmp[x + 1] == ' ' && map_line[x + 1] != ' ')))
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
