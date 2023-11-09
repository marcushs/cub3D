/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:13:52 by hleung            #+#    #+#             */
/*   Updated: 2023/11/09 16:16:12 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_config(t_config *config);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		init_data(&data, argv[1]);
		hooks_and_loops(&data);
		free_data(&data);
	}
	else
		ft_putstr("Wrong number of arguments!\n");
}
