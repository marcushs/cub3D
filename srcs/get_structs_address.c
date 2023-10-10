/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_structs_address.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:37:24 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/05 13:00:24 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_data	*get_data_address(t_data* data)
{
	static t_data	*tmp;

	if (data == NULL)
		return (tmp);
	tmp = data;
	return (tmp);
}

t_mlx	*get_mlx_address(t_mlx* mlx)
{
	static t_mlx	*tmp;

	if (mlx == NULL)
		return (tmp);
	tmp = mlx;
	return (tmp);
}

t_config	*get_config_address(t_config* config)
{
	static t_config	*tmp;

	if (config == NULL)
		return (tmp);
	tmp = config;
	return (tmp);
}

t_player	*get_player_address(t_player *player)
{
	static t_player	*tmp;

	if (player == NULL)
		return (tmp);
	tmp = player;
	return (tmp);
}
