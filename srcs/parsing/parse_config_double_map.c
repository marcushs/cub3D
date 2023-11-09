/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_double_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:15:21 by tduprez           #+#    #+#             */
/*   Updated: 2023/11/09 16:41:44 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char	**copy_map(t_config *config);
static void	ft_diffusion(t_config *config, char ***map, int y, int x);
static bool	check_for_diffusion(t_config *config, char **map, int y, int x);
static bool	check_map(t_config *config, char **map);

void	check_double_map(t_config *config)
{
	int		x;
	char	**map;

	x = 0;
	map = copy_map(config);
	while (config->map[0][x] && config->map[0][x] == ' ')
		x++;
	ft_diffusion(config, &map, 0, x);
	if (check_map(config, map) == true)
	{
		free_2d_char(&map, config->map_size);
		free_config_exit_msg(config, EXIT_FAILURE, MAP_LAST);
	}
	free_2d_char(&map, config->map_size);
	return ;
}

char	**copy_map(t_config *config)
{
	int		y;
	char	**map;

	y = 0;
	map = malloc(sizeof(char *) * config->map_size);
	if (!map)
		free_config_exit_msg(config, EXIT_FAILURE, MALLOC_ERR);
	while (y < config->map_size)
	{
		map[y] = ft_strdup(config->map[y]);
		y++;
	}
	return (map);
}

static void	ft_diffusion(t_config *config, char ***map, int y, int x)
{
	(*map)[y][x] = '*';
	if (check_for_diffusion(config, (*map), y, x + 1) == true)
		ft_diffusion(config, map, y, x + 1);
	if (check_for_diffusion(config, (*map), y, x - 1) == true)
		ft_diffusion(config, map, y, x - 1);
	if (check_for_diffusion(config, (*map), y + 1, x) == true)
		ft_diffusion(config, map, y + 1, x);
	if (check_for_diffusion(config, (*map), y - 1, x) == true)
		ft_diffusion(config, map, y - 1, x);
	return ;
}

static bool	check_for_diffusion(t_config *config, char **map, int y, int x)
{
	if (x >= 0 && y >= 0 && y < config->map_size && x < (int)ft_strlen(map[y]) \
	&& map[y][x] && map[y][x] != ' ' && map[y][x] != '*')
		return (true);
	return (false);
}

static bool	check_map(t_config *config, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (y < config->map_size)
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (map[y][x] != ' ' && map[y][x] != '*')
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}
