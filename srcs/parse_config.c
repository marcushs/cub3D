/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:36:21 by hleung            #+#    #+#             */
/*   Updated: 2023/09/29 23:38:40 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	parse_element(t_config *config, char *line);
int	elements_loop(t_config *config, int fd);
int	elements_conditions(t_config *config, char ***strs, char **path);
int	parse_rgb(t_config *config, char **str, char c);
int	map_loop(t_config *config, int fd);

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
	map_loop(config, fd);
}

int	elements_loop(t_config *config, int fd)
{
	int		elem_ctr;
	char	*line;

	elem_ctr = 0;
	line = get_next_line(fd);
	while (line && elem_ctr < 6)
	{
		if (!is_empty_line(line))
		{
			printf("%s", line);
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

int	parse_element(t_config *config, char *line)
{
	char	**strs;
	char	*path;

	strs = ft_split(line, ' ');
	if (!strs)
		return (ft_putstr(MALLOC_ERR), -1);
	if (!strs[1])
		return (free_2d_char(&strs), ft_putstr(NO_PATH), -1);
	path = ft_substr(strs[1], 0, ft_strlen(strs[1]) - 1);
	if (!path)
		return (free_2d_char(&strs), ft_putstr(MALLOC_ERR), -1);
	if (elements_conditions(config, &strs, &path) == -1)
		return (-1);
	free_2d_char(&strs);
	return (0);
}

int	elements_conditions(t_config *config, char ***strs, char **path)
{

	if (!ft_strcmp((*strs)[0], "NO"))
		config->path_to_NO = *path;
	else if (!ft_strcmp((*strs)[0], "SO"))
		config->path_to_SO = *path;
	else if (!ft_strcmp((*strs)[0], "WE"))
		config->path_to_WE = *path;
	else if (!ft_strcmp((*strs)[0], "EA"))
		config->path_to_EA = *path;
	else if (!ft_strcmp((*strs)[0], "F"))
	{
		if (parse_rgb(config, path, 'F') == -1)
			return (free_set_null(path), free_2d_char(strs), -1);
	}
	else if (!ft_strcmp((*strs)[0], "C"))
	{
		if (parse_rgb(config, path, 'C') == -1)
			return (free_set_null(path), free_2d_char(strs), -1);
	}
	else
		return (free_set_null(path), free_2d_char(strs), ft_putstr(INV_ID), -1);
	return (0);
}

int	parse_rgb(t_config *config, char **str, char c)
{
	char	**values;
	int		i;
	int		value;

	values = ft_split(*str, ',');
	if (!values)
		return (ft_putstr(MALLOC_ERR), -1);
	free_set_null(str);
	i = 0;
	while (values[i])
	{
		value = ft_atoi(values[i]);
		if (value < 0 || value > 255)
			return (ft_putstr(OUT_RANGE), -1);
		if (c == 'F')
			config->floor_rgb[i] = value;
		else
			config->ceiling_rgb[i] = value;
		i++;
	}
	free_2d_char(&values);
	return (0);
}

int	map_loop(t_config *config, int fd)
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
		printf("%s", line);
		tmp = ft_strdup(line);
		if (!tmp)
			return (ft_putstr(MALLOC_ERR), -1);
		new = ft_lstnew(tmp);
		if (!new)
			return (ft_putstr(MALLOC_ERR), -1);
		ft_lstadd_back(&config->map_list, new);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
