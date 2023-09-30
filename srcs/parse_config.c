/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:36:21 by hleung            #+#    #+#             */
/*   Updated: 2023/09/30 16:56:22 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void			parse_config(t_config *config, char *path);
static int		map_loop(t_config *config, int fd);
static int		elements_loop(t_config *config, int fd);

void	parse_config(t_config *config, char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("%s file not found\n", path);
		exit(EXIT_FAILURE);
	}
	if (elements_loop(config, fd) == -1)
	{
		free_config(config);
		exit(EXIT_FAILURE);
	}
	if (map_loop(config, fd) == -1)
	{
		free_config(config);
		exit(EXIT_FAILURE);
	}
}

static int	elements_loop(t_config *config, int fd)
{
	int		elem_ctr;
	char	*line;

	elem_ctr = 0;
	line = get_next_line(fd);
	while (line && elem_ctr < 6)
	{
		if (!is_empty_line(line))
		{
			if (parse_element(config, line) == -1)
				return (free(line), -1);
			elem_ctr++;
		}
		free(line);
		line = get_next_line(fd);
	}
	while (line && is_empty_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	config->map_tmp = line;
	return (0);
}

static int	map_loop(t_config *config, int fd)
{
	char	*line;
	char	*tmp;
	t_list	*new;

	tmp = NULL;
	line = config->map_tmp;
	while (line)
	{
		if (is_empty_line(line))
			return (ft_putstr(MAP_EMPTY), -1);
		tmp = ft_strdup(line);
		if (!tmp)
			return (free_set_null(&config->map_tmp), \
			ft_putstr(MALLOC_ERR), -1);
		new = ft_lstnew(tmp);
		if (!new)
			return (free_set_null(&config->map_tmp), \
			free_set_null(&tmp), ft_putstr(MALLOC_ERR), -1);
		ft_lstadd_back(&config->map_list, new);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
