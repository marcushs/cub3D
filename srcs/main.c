/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:13:52 by hleung            #+#    #+#             */
/*   Updated: 2023/09/21 14:49:29 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 2)
	{
		if (parse_map(&map, argv[1]) == -1)
			return (1);
	}
	else
		ft_putstr("Wrong number of arguments!\n");
}