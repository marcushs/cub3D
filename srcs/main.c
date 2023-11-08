/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:13:52 by hleung            #+#    #+#             */
/*   Updated: 2023/11/03 09:07:58 by hleung           ###   ########.fr       */
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
		// get_config_address(&config);
		// parse_config(&config);
		// render(&config);
		// print_config(&config); //debug function
		// free_config(&config);
	}
	else
		ft_putstr("Wrong number of arguments!\n");
}

void	print_config(t_config *config)
{
	//t_list	*tmp;

	printf("NO: %s\n", config->text_paths[0]);
	printf("SO: %s\n", config->text_paths[2]);
	printf("WE: %s\n", config->text_paths[3]);
	printf("EA: %s\n", config->text_paths[1]);
	printf("-------------------------\n");
	printf("F: ");
	for (int i = 0; i < 3; i++)
		printf("%d ", config->floor_rgb[i]);
	printf("\n");
	printf("C: ");
	for (int i = 0; i < 3; i++)
		printf("%d ", config->ceiling_rgb[i]);
	printf("\n");
	//printf("-------------------------\n");
	/* Pour ce commit je print la mappe en liste chainee, le prochain commit je remet la liste en tablea 2D
	si besoin de print map en list, enleve lstclear dans fonction "map_list_to_arr"*/
	
	// tmp = config->map_list;
	// while (tmp)
	// {
	// 	printf("%s", (char *)tmp->content);
	// 	tmp = tmp->next;
	// }
	printf("-------------------------\n");
	/* Print map en tableau 2D */
	for (int i = 0; i < config->map_size; i++)
		printf("%s", config->map[i]);
}
