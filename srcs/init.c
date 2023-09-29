/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:29:49 by hleung            #+#    #+#             */
/*   Updated: 2023/09/29 21:18:06 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	config_init(t_config *config)
{
	config->path_to_NO = NULL;
	config->path_to_SO = NULL;
	config->path_to_WE = NULL;
	config->path_to_EA = NULL;
	config->map_tmp = NULL;
	config->map_list = NULL;
}
