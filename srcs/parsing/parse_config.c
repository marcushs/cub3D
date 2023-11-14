/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:36:21 by hleung            #+#    #+#             */
/*   Updated: 2023/10/18 22:55:11 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int		elements_loop(t_config *config, int fd);
static int		map_loop(t_config *config, int fd);
static int		convert_map_list_to_array(t_config *config);
static int		check_map_chars(t_config *config);

void	parse_config(t_config *config)
{
	if (elements_loop(config, config->fd) == -1)
		free_config_exit_msg(config, EXIT_FAILURE, NULL);
	if (map_loop(config, config->fd) == -1)
		free_config_exit_msg(config, EXIT_FAILURE, NULL);
	if (convert_map_list_to_array(config) == -1)
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

static int	convert_map_list_to_array(t_config *config)
{
	int		i;
	t_list	*tmp;

	if (!config->map_list)
		return (ft_putstr(NO_MAP), -1);
	config->map_size = ft_lstsize(config->map_list);
	config->map = (char **)malloc(sizeof(char *) * config->map_size);
	if (!config->map)
		return (ft_putstr(MALLOC_ERR), -1);
	set_map_null(config);
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

static int	check_map_chars(t_config *config)
{
	int	i;
	int	j;
	int	chars[256];

	i = -1;
	while (++i < 256)
		chars[i] = 0;
	i = -1;
	while (++i < config->map_size)
	{
		j = -1;
		while (config->map[i][++j])
			chars[(int)config->map[i][j]]++;
	}
	if (chars[69] + chars[78] + chars[83] + chars[87] != 1)
		return (ft_putstr(POV_ERR), -1);
	i = -1;
	while (++i < 256)
		if ((i != 10 && i != 32 && i != 48 && i != 49 && i != 69 && \
			i != 78 && i != 83 && i != 87) && chars[i])
			return (ft_putstr(INV_CHAR), -1);
	return (0);
}
