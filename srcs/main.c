/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:13:52 by hleung            #+#    #+#             */
/*   Updated: 2023/10/02 09:12:10 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_config(t_config *config);

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc == 2)
	{
		config_init(&config);
		parse_config(&config, argv[1]);
		print_config(&config); //debug function
		free_config(&config);
	}
	else
		ft_putstr("Wrong number of arguments!\n");
}

void	print_config(t_config *config)
{
	t_list	*tmp;
	int		size;

	size = ft_lstsize(config->map_list);
	printf("NO: %s\n", config->path_to_no);
	printf("SO: %s\n", config->path_to_so);
	printf("WE: %s\n", config->path_to_we);
	printf("EA: %s\n", config->path_to_ea);
	printf("-------------------------\n");
	printf("F: ");
	for (int i = 0; i < 3; i++)
		printf("%d ", config->floor_rgb[i]);
	printf("\n");
	printf("C: ");
	for (int i = 0; i < 3; i++)
		printf("%d ", config->ceiling_rgb[i]);
	printf("\n");
	printf("-------------------------\n");
	/* Pour ce commit je print la mappe en liste chainee, le prochain commit je remet la liste en tablea 2D*/
	tmp = config->map_list;
	while (tmp)
	{
		printf("%s", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("-------------------------\n");
	/* Print map en tableau 2D */
	for (int i = 0; i < size; i++)
	{
		printf("%s", config->map[i]);
	}
}
