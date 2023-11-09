// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   put_to_mlx.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/10/14 13:25:36 by tduprez           #+#    #+#             */
// /*   Updated: 2023/10/27 11:21:03 by tduprez          ###   ########lyon.fr   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/cub3D.h"

// static void put_one_vector(t_data *data, float angle, int color);

// void put_square(t_mlx *mlx, float x, float y, int player)
// {
// 	float start_x;
// 	float start_y;
// 	float end_x;
// 	float end_y;

// 	start_x = (x + 1) * 15 + ((player * -0.20) * 15);
// 	start_y = (y + 1) * 15 + ((player * -0.20) * 15);
// 	end_x = start_x + 14 + (player * -7);
// 	end_y = start_y + 14 + (player * -7);
// 	while (start_y < end_y)
// 	{
// 		while (start_x < end_x)
// 		{
// 			if (player)
// 				put_pixel(mlx->mini_map, start_x, start_y, 0x00FF0000);
// 			else
// 				put_pixel(mlx->mini_map, start_x, start_y, 0x00999999);
// 			start_x++;
// 		}
// 		start_x -= 14 - (player * 7);
// 		start_y++;
// 	}
// 	return ;
// }

// void put_vectors(t_data *data)
// {
// 	float range;
// 	float i;

// 	range = (30.0 / 180.0) * PI;
// 	i = -range;
// 	data->r_count = 0;
// 	while (i < range)
// 	{
// 		i += 0.05;
// 		data->r_count++;
// 	}
// 	data->rays = (t_ray *)malloc(sizeof(t_ray) * data->r_count); //need protection
// 	i = -range;
// 	while (i < range)
// 	{
// 		put_one_vector(data, data->player->angle + i, 0x00FF0000);
// 		i += 0.05;
// 	}
// 	put_one_vector(data, data->player->angle, 0x00FF00);
// 	return ;
// }

// void put_one_vector(t_data *data, float angle, int color)
// {
// 	t_image	*mini_map;

// 	mini_map = data->mlx->mini_map;
// 	float vector_x = data->player->coor->x;
// 	float vector_y = data->player->coor->y;
// 	float step_size = 0.01;
// 	float len = 0.00;

// 	while (data->config->map[(int)vector_y] && 
// 	data->config->map[(int)vector_y][(int)vector_x] != '1' && len < 8.0)
// 	{
// 		put_pixel(mini_map, (vector_x + 1) * 15, (vector_y + 1) * 15, color);
// 		vector_x += cos(angle) * step_size;
// 		vector_y -= sin(angle) * step_size;
// 		len += step_size;
// 	}
// 	// if (color == 0x00FF0000)
// 	// 	set_rays_dist(data, vector_x, vector_y);
// 	// float lineH = (15 * 15 * 950)/ray_dis; if (lineH > 950){lineH = 950;}
// 	return;
// }

// void    ft_put_img_to_img(t_image *img_1, t_image *img_2, int x, int y)
// {
//     int    *data_1;
//     int    *data_2;
//     int    i;
//     int    j;

//     i = 0;
//     if (y < 0)
//         i = -y;
//     data_1 = ((int *)img_1->img_addr) + (img_1->width * (y + i) + x);
//     data_2 = ((int *)img_2->img_addr) + (img_2->width * i);
//     while (i < (img_1->height - y) && i < img_2->height)
//     {
//         if (x < 0)
//             j = -x;
//         else
//             j = 0;
//         while (j < (img_1->width - x) && j < img_2->width)
//         {
//             data_1[j] = data_2[j];
//             j++;
//         }
//         data_1 += img_1->width;
//         data_2 += img_2->width;
//         i++;
//     }
// }


// void put_pixel(t_image *image, int x, int y, int color)
// {
// 	char *dst;

// 	dst = image->img_addr + (y * image->line_len + x * (image->bpp / 8));
// 	*(unsigned int *)dst = color;
// 	return;
// }
