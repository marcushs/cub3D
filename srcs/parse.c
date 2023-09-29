/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:36:21 by hleung            #+#    #+#             */
/*   Updated: 2023/09/29 12:05:19 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_empty_line(char *line);
int	parse_element(t_map *map, char *line);

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
		if (!check_empty_line(line))
		{
			printf("%s", line);
			parse_element(map, line);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

int	parse_element(t_map *map, char *line)
{
	char	**strs;
	(void)map;
	strs = ft_split_space(line);
	if (!strs)
		return (-1);
	if (!ft_strcmp(strs[0], "NO"))
		printf("NO: %s\n", strs[1]);
	else if (!ft_strcmp(strs[0], "SO"))
		printf("SO: %s\n", strs[1]);
	else if (!ft_strcmp(strs[0], "WE"))
		printf("WE: %s\n", strs[1]);
	else if (!ft_strcmp(strs[0], "EA"))
		printf("EA: %s\n", strs[1]);
	else if (!ft_strcmp(strs[0], "F"))
		printf("F: %s\n", strs[1]);
	else if (!ft_strcmp(strs[0], "C"))
		printf("C: %s\n", strs[1]);
	else
		printf("Error\n");
	free_2d_array((void ***)&strs, 2);
	printf("strs[0] = %s, add = %p\n", strs[0], strs[0]);
	printf("strs[1] = %s, add = %p\n", strs[1], strs[1]);
	printf("strs add = %p\n", strs);
	return (1);
}
