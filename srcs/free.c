/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:42:48 by hleung            #+#    #+#             */
/*   Updated: 2023/09/30 16:54:53 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_set_null(char **arr);
void	free_2d_char(char ***arr);
void	free_config(t_config *config);

void	free_set_null(char **arr)
{
	free(*arr);
	*arr = NULL;
}

void	free_2d_char(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free_set_null(&(*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

void	free_config(t_config *config)
{
	if (config->path_to_NO)
		free_set_null(&config->path_to_NO);
	if (config->path_to_SO)
		free_set_null(&config->path_to_SO);
	if (config->path_to_WE)
		free_set_null(&config->path_to_WE);
	if (config->path_to_EA)
		free_set_null(&config->path_to_EA);
	if (config->map_list)
		ft_lstclear(&config->map_list, &free);
}
