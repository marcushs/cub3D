/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:29:49 by hleung            #+#    #+#             */
/*   Updated: 2023/10/14 13:16:19 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	is_valid_file_extension(char *path);

void	init_config(t_config *config, char *map_path)
{
	config->fd = -1;
	config->path_to_no = NULL;
	config->path_to_so = NULL;
	config->path_to_we = NULL;
	config->path_to_ea = NULL;
	config->map_tmp = NULL;
	config->map_list = NULL;
	config->map_size = 0;
	config->map_row = 0;
	config->map = NULL;
	if (!is_valid_file_extension(map_path))
	{
		printf(INV_EXT);
		exit(EXIT_FAILURE);
	}
	config->fd = open(map_path, O_RDONLY);
	if (config->fd == -1)
	{
		printf("%s file not found\n", map_path);
		exit(EXIT_FAILURE);
	}
}

int	is_valid_file_extension(char *path)
{
	path = ft_strchr(path, '.');
	if (!path)
		return (0);
	if (!ft_strcmp(path, ".cub"))
		return (1);
	return (0);
}
