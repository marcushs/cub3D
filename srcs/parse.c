/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:36:21 by hleung            #+#    #+#             */
/*   Updated: 2023/09/21 14:49:37 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	parse_map(t_map *map, char *path)
{
	(void)map;
	int		fd;
	char	*line;
	
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("%s file not found\n", path);
		return (-1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
