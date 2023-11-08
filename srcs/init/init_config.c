/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:29:49 by hleung            #+#    #+#             */
/*   Updated: 2023/11/08 09:28:38 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_valid_file_extension(char *path);

void	init_config(t_config *config, char *map_path)
{
	config->fd = -1;
	config->map_tmp = NULL;
	config->map_list = NULL;
	config->map_size = 0;
	config->map_row = 0;
	config->map = NULL;
	config->text_paths = (char **)malloc(sizeof(char *) * 4);
	if (!config->text_paths)
	{
		ft_putstr_fd(MALLOC_ERR, 2);
		exit(EXIT_FAILURE);
	}
	if (!is_valid_file_extension(map_path))
	{
		ft_putstr_fd(INV_EXT, 2);
		exit(EXIT_FAILURE);
	}
	config->fd = open(map_path, O_RDONLY);
	if (config->fd == -1)
	{
		printf("%s file not found\n", map_path);
		exit(EXIT_FAILURE);
	}
	parse_config(config);
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
