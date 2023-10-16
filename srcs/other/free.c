/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:42:48 by hleung            #+#    #+#             */
/*   Updated: 2023/10/16 09:17:05 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_set_null(char **arr);
void	free_2d_char(char ***arr, int size);
void	free_config(t_config *config);

void	free_set_null(char **arr)
{
	if (*arr != NULL)
	{
		free(*arr);
		*arr = NULL;
	}
}

void	free_2d_char(char ***arr, int size)
{
	while (--size >= 0)
		free_set_null(&(*arr)[size]);
	free(*arr);
	*arr = NULL;
}

void	free_config(t_config *config)
{
	if (config->path_to_no)
		free_set_null(&config->path_to_no);
	if (config->path_to_so)
		free_set_null(&config->path_to_so);
	if (config->path_to_we)
		free_set_null(&config->path_to_we);
	if (config->path_to_ea)
		free_set_null(&config->path_to_ea);
	if (config->map_list)
		ft_lstclear(&config->map_list, &free);
	if (config->map)
		free_2d_char(&config->map, config->map_size);
	if (config->fd != -100)
		close(config->fd);
}

void	free_config_exit_msg(t_config *config, int status, const char *msg)
{
	if (msg)
		printf("%s", msg);
	free_config(config);
	exit(status);
}
