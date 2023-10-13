/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:36:21 by hleung            #+#    #+#             */
/*   Updated: 2023/10/13 14:19:45 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void			parse_config(t_config *config, char *path);
static int		map_loop(t_config *config, int fd);
static int		elements_loop(t_config *config, int fd);
static int		is_val_file_ext(char *path);
static int		map_list_to_arr(t_config *config);

void	parse_config(t_config *config, char *path)
{
	if (!is_val_file_ext(path))
	{
		printf(INV_EXT);
		exit(EXIT_FAILURE);
	}
	config->fd = open(path, O_RDONLY);
	if (config->fd == -1)
	{
		printf("%s file not found\n", path);
		exit(EXIT_FAILURE);
	}
	if (elements_loop(config, config->fd) == -1)
		free_config_exit_msg(config, EXIT_FAILURE, NULL);
	if (map_loop(config, config->fd) == -1)
		free_config_exit_msg(config, EXIT_FAILURE, NULL);
	if (map_list_to_arr(config) == -1)
		free_config_exit_msg(config, EXIT_FAILURE, NULL);
	if (check_map_chars(config) == -1)
		free_config_exit_msg(config, EXIT_FAILURE, NULL);
	trim_map_first_spaces(config);
	trim_map_back_spaces(config);
	check_walls(config);
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
	close(config->fd);
	config->fd = -100;
	return (0);
}

static int	is_val_file_ext(char *path)
{
	path = ft_strchr(path, '.');
	if (!path)
		return (0);
	if (!ft_strcmp(path, ".cub"))
		return (1);
	return (0);
}

static int	map_list_to_arr(t_config *config)
{
	int		i;
	t_list	*tmp;

	if (!config->map_list)
		return (ft_putstr(NO_MAP), -1);
	config->map_size = ft_lstsize(config->map_list);
	config->map = (char **)malloc(sizeof(char *) * config->map_size);
	if (!config->map)
		return (ft_putstr(MALLOC_ERR), -1);
	tmp = config->map_list;
	i = 0;
	while (i < config->map_size)
	{
		config->map[i] = ft_strdup(tmp->content);
		if (!config->map[i])
			return (ft_putstr(MALLOC_ERR), -1);
		i++;
		tmp = tmp->next;
	}
	ft_lstclear(&config->map_list, &free);
	config->map_list = NULL;
	if (trim_empty_lines_after_map(config) == -1)
		return (-1);
	return (0);
}
