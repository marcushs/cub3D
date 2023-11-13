/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:36:21 by hleung            #+#    #+#             */
/*   Updated: 2023/11/13 11:29:47 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	check_line(t_config *config, char *line);
void		ft_diffusion(t_config *c, char ***map, int y, int x);
void		check_double_map(t_config *config);
static void	check_open_walls(t_config *config, int x, int y);

int	check_walls(t_config *config)
{
	int	x;
	int	y;

	y = 1;
	check_line(config, config->map[0]);
	check_line(config, config->map[config->map_size - 1]);
	while (y < config->map_size - 1)
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
	check_double_map(config);
	return (0);
}

static void	check_line(t_config *config, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0')
			free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
		i++;
	}
	return ;
}

static void	check_open_walls(t_config *config, int x, int y)
{
	if (config->map[y - 1][x] && (config->map[y - 1][x] == ' ' \
	|| config->map[y - 1][x] == '\n'))
		free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
	if (config->map[y + 1][x] && (config->map[y + 1][x] == ' ' \
	|| config->map[y + 1][x] == '\n'))
		free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
	if (config->map[y][x - 1] && (config->map[y][x - 1] == ' ' \
	|| config->map[y][x - 1] == '\n'))
		free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
	if (config->map[y][x + 1] && (config->map[y][x + 1] == ' ' \
	|| config->map[y][x + 1] == '\n'))
		free_config_exit_msg(config, EXIT_FAILURE, WALL_ERR);
	return ;
}
