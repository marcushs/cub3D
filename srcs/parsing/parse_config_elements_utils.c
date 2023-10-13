/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_elements_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:56:15 by hleung            #+#    #+#             */
/*   Updated: 2023/10/13 18:26:13 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char	*join_line(char *s1, char *s2);

int	is_map_content(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i + 1] && str[i] == 'W' && str[i + 1] == 'E')
	{
		i = 0;
		while (str[i] && ft_isspace(str[i]))
			i++;
		return (0);
	}
	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' \
		|| c == 'W' || c == 'E' || c == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

int	count_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	join_strs(char ***strs, char **tmp)
{
	int		i;

	i = 0;
	while ((*strs)[++i])
	{
		*tmp = join_line(*tmp, (*strs)[i]);
		if (!*tmp)
			return (free_2d_char(strs, count_strs((*strs))), \
			ft_putstr(MALLOC_ERR), -1);
	}
	if ((*tmp)[0] == ',')
		return (free_2d_char(strs, count_strs((*strs))), \
		free_set_null(tmp), ft_putstr(NB_VALUE), -1);
	return (0);
}

static char	*join_line(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1)
		join = (char *)malloc(ft_strlen(s2) + 1);
	else
		join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (free(s1), s1 = NULL, NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
		join[i++] = s2[j++];
	join[i] = 0;
	return (free(s1), s1 = NULL, join);
}
