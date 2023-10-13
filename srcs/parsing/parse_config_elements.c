/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:12:06 by hleung            #+#    #+#             */
/*   Updated: 2023/10/13 18:25:31 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	elements_conditions(t_config *config, char ***strs);
static int	parse_texture_path(t_config *config, char ***strs);
static int	parse_rgb(t_config *config, char ***strs);
static int	str_to_rgb_values(t_config *config, char ***values, char *c);

int	parse_element(t_config *config, char *line)
{
	char	**strs;

	if (is_map_content(line))
		return (ft_putstr(MAP_LAST), -1);
	strs = ft_split(line, ' ');
	if (!strs)
		return (ft_putstr(MALLOC_ERR), -1);
	if (count_strs(strs) < 2 || is_empty_line(strs[1]))
		return (free_2d_char(&strs, count_strs(strs)), ft_putstr(NO_PATH), -1);
	if (elements_conditions(config, &strs) == -1)
		return (-1);
	free_2d_char(&strs, count_strs(strs));
	return (0);
}

static int	elements_conditions(t_config *config, char ***strs)
{
	char	*id;

	id = (*strs)[0];
	if (!ft_strcmp(id, "NO") || !ft_strcmp(id, "SO") || \
	!ft_strcmp(id, "WE") || !ft_strcmp(id, "EA"))
	{
		if (parse_texture_path(config, strs) == -1)
			return (-1);
	}
	else if (!ft_strcmp(id, "F") || !ft_strcmp(id, "C"))
	{
		if (parse_rgb(config, strs) == -1)
			return (-1);
	}
	else
		return (free_2d_char(strs, count_strs(*strs)), ft_putstr(INV_ID), -1);
	return (0);
}

static int	parse_texture_path(t_config *config, char ***strs)
{
	char	*path;
	int		i;

	path = NULL;
	if (count_strs(*strs) > 2)
	{
		i = 1;
		while ((*strs)[++i])
			if (!is_empty_line((*strs)[i]))
				return (free_2d_char(strs, count_strs(*strs)), \
				ft_putstr(MUL_PATH), -1);
	}
	path = ft_substr((*strs)[1], 0, ft_strlen((*strs)[1]) - 1);
	if (!path)
		return (free_2d_char(strs, count_strs(*strs)), \
		ft_putstr(MALLOC_ERR), -1);
	if (!ft_strcmp((*strs)[0], "NO"))
		config->path_to_no = path;
	else if (!ft_strcmp((*strs)[0], "SO"))
		config->path_to_so = path;
	else if (!ft_strcmp((*strs)[0], "WE"))
		config->path_to_we = path;
	else if (!ft_strcmp((*strs)[0], "EA"))
		config->path_to_ea = path;
	return (0);
}

static int	parse_rgb(t_config *config, char ***strs)
{
	char	**values;
	char	*tmp;

	values = NULL;
	tmp = NULL;
	if (count_strs(*strs) > 2)
	{
		if (join_strs(strs, &tmp) == -1)
			return (-1);
	}
	else
		tmp = (*strs)[1];
	values = ft_split(tmp, ',');
	if (count_strs(*strs) > 2)
		free_set_null(&tmp);
	if (!values)
		return (free_2d_char(strs, count_strs(*strs)), \
		ft_putstr(MALLOC_ERR), -1);
	if (count_strs(values) != 3)
		return (free_2d_char(&values, count_strs(values)), \
		free_2d_char(strs, count_strs(*strs)), ft_putstr(NB_VALUE), -1);
	if (str_to_rgb_values(config, &values, (*strs)[0]) == -1)
		return (free_2d_char(strs, count_strs(*strs)), -1);
	return (0);
}

static int	str_to_rgb_values(t_config *config, char ***values, char *c)
{
	int	i;
	int	j;
	int	value;

	i = -1;
	while ((*values)[++i])
	{
		j = -1;
		if (!(*values)[i][0] || (*values)[i][0] == '\n')
			return (free_2d_char(values, count_strs(*values)), \
				ft_putstr(NB_VALUE), -1);
		while ((*values)[i][++j])
			if (!ft_isdigit((*values)[i][j]) && (*values)[i][j] != '\n')
				return (free_2d_char(values, count_strs(*values)), \
				ft_putstr(NON_NUM), -1);
		value = ft_atoi((*values)[i]);
		if (value < 0 || value > 255)
			return (free_2d_char(values, count_strs(*values)), \
			ft_putstr(OUT_RANGE), -1);
		if (*c == 'F')
			config->floor_rgb[i] = value;
		else
			config->ceiling_rgb[i] = value;
	}
	return (free_2d_char(values, count_strs(*values)), 0);
}
