/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:36:21 by hleung            #+#    #+#             */
/*   Updated: 2023/10/17 17:52:15 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	check_line(t_config *config, char *line);
static void	check_open_walls(t_config *config, int x, int y);
char		**ft_diffusion(t_config *c, char **map, int y, int x);
bool		check_double_map(t_config *config);

int	check_walls(t_config *config)
{
	int	x;
	int	y;

	y = 1;
	check_line(config, config->map[0]);
	check_line(config, config->map[config->map_size - 1]);
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
	if (check_double_map(config) == true)
		exit (1);
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

bool	check_double_map(t_config *config)
{
	int		x;
	int		y;
	char	**map;

	y = -1;
	map = malloc(sizeof(char *) * config->map_size);
	if (!map)
		free_config_exit_msg(config, EXIT_FAILURE, MALLOC_ERR);
	while (++y < config->map_size)
		map[y] = ft_strdup(config->map[y]);
	x = 0;
	while (config->map[0][x] && config->map[0][x] == ' ')
		x++;
	ft_diffusion(config, map, 0, x);
	y = -1;
	while (++y < config->map_size)
	{
		x = -1;
		while (map[y][++x] && map[y][x] != '\n')
			if (map[y][x] != ' ' && map[y][x] != '*')
				return (printf("%c | %d\n", map[y][x], map[y][x]), free_2d_char(&map, config->map_size), true);
	}
	return (free_2d_char(&map, config->map_size), false);
}

char	**ft_diffusion(t_config *c, char **map, int y, int x)
{
	if ((y >= 0 && x >= 0 && y < c->map_size && x < (int)ft_strlen(map[y]) && map[y][x] && map[y][x] != ' ' && map[y][x] != '\n' && map[y][x] != '*'))
	{
		// for (int i = 0; i < c->map_size; i++)
		// {
		// 	for (int j = 0; map[i][j]; j++)
		// 	{
		// 		printf("%c", map[i][j]);
		// 	}
		// }
		map[y][x] = '*';
		if (y >= 0 && y < c->map_size && x + 1 <= (int)ft_strlen(map[y]) && map[y][x + 1] && map[y][x + 1] != ' ' && map[y][x + 1] != '*')
			ft_diffusion(c, map, y, x + 1);
		if (y >= 0 && x - 1 >= 0 && y < c->map_size && x < (int)ft_strlen(map[y]) && map[y][x - 1] && map[y][x - 1] != ' ' && map[y][x - 1] != '*')
			ft_diffusion(c, map, y, x - 1);
		if (y >= 0 && x >= 0 && y + 1 < c->map_size && x < (int)ft_strlen(map[y]) && map[y + 1][x] && map[y + 1][x] != ' ' && map[y + 1][x] != '*')
			ft_diffusion(c, map, y + 1, x);
		if (y - 1 >= 0 && x >= 0 && y < c->map_size && x < (int)ft_strlen(map[y]) && map[y - 1][x] && map[y - 1][x] != ' ' && map[y - 1][x] != '*')
			ft_diffusion(c, map, y - 1, x);
	}
	return (map);
}
