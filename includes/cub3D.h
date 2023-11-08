/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:22:33 by hleung            #+#    #+#             */
/*   Updated: 2023/11/08 11:00:37 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "structs_and_macros.h"

/* Prototypes */

/* init_config.c */
void	    init_config(t_config *config, char *map_path);

/* init_data.c */
void		init_data(t_data *data, char *map_path);
void		init_player_hitbox(t_player *player);

/* parse_config.c */
void		parse_config(t_config *config);

/* parse_config_utils.c */
int			is_empty_line(char *line);
void		set_map_null(t_config *config);
int			trim_empty_lines_after_map(t_config *config);
void		trim_map_first_spaces(t_config *config);
void		trim_map_back_spaces(t_config *config);

/* parse_config_elements.c */
int			parse_element(t_config *config, char *line);

/* parse_config_elements_utils.c*/
int			is_map_content(char *str);
int			count_strs(char **strs);
int			join_strs(char ***strs, char **tmp);

/* parse_config_walls */
int			check_walls(t_config *config);

/* parse_config_double_map.c */
void		check_double_map(t_config *config);

/* render.c */
void		render(t_config *config);
void		render_minimap(t_data *data);
void		render_player(t_image *player);
void		put_window_image_to_window(t_mlx *mlx, float x, float y);

/* render_utils.c */
int			map_longest_row(t_config *config);
void		init_image_data(t_mlx *mlx, t_config *config);

/* put_to_mlx.c */
void		put_square(t_mlx *mlx, float x, float y, int player);
void		put_vectors(t_data *data);
void		ft_put_img_to_img(t_image *img1, t_image *img2, int x, int y);
void		put_pixel(t_image *image, int x, int y, int color);

/* move.c */
void		move_player(int keycode, t_data *data);

/* event.c */
int			event_move(int keycode, t_mlx* mlx);
int			event_close(t_mlx *mlx);

/* free.c */
void		free_set_null(char **arr);
void		free_config(t_config *config);
void		free_2d_char(char ***arr, int size);
void		free_config_exit_msg(t_config *config, int status, const char* msg);
void		free_data(t_data *data);

/* get_structs_address.c */
t_data		*get_data_address(t_data* data);
t_mlx		*get_mlx_address(t_mlx* mlx);
t_config	*get_config_address(t_config* config);

/* render_3d.c */
void	draw_3d_walls(t_data *data);
void	dda(t_data *data);

#endif
