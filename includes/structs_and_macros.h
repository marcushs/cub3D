/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_and_macros.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:03:25 by hleung            #+#    #+#             */
/*   Updated: 2023/11/08 13:28:11 by hleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_AND_MACROS_H
# define STRUCTS_AND_MACROS_H

/* Header files */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

/* Error messages */
# define INV_ID "Error:\nInvalid identifier!\n"
# define INV_EXT "Error:\nInvalid file extension (expected `.cub')!\n"
# define MAP_LAST "Error:\nMap content misplaced or missing element!\n"
# define NO_PATH "Error:\nNo path or value specified!\n"
# define MUL_PATH "Error:\nMore than one path specified!\n"
# define NB_VALUE "Error:\nWrong number of RGB values!\n"
# define NON_NUM "Error:\nOnly numerical values allowed!\n"
# define OUT_RANGE "Error:\nValue out of range!\n"
# define NO_MAP "Error:\nNo map given!\n"
# define MAP_EMPTY "Error:\nEmpty line in map content!\n"
# define INV_CHAR "Error:\nInvalid character in map!\n"
# define POV_ERR "Error:\nNeed one and only one player in map!\n"
# define WALL_ERR "Error:\nMap not enclosed by wall!\n"
# define MALLOC_ERR "Malloc error!\n"
# define TEXT_ERR "Error:\nCannot load texture %s\n!"

/* Keycodes*/
# define XK_w 119 % 200
# define XK_d 100 % 200
# define XK_s 115 % 200
# define XK_a 97 % 200
# define XK_left 65361 % 200
# define XK_right 65363 % 200
# define XK_esc 65307 % 200

/* Values */
# define PI 3.1415926535
# define M_PI	3.14159265358979323846
# define M_PI_2	1.57079632679489661923
# define WIN_H 1080
# define WIN_W 1920
# define PLAYER_H 8
# define PLAYER_W 8
# define MAP_H 200
# define MAP_W 200
# define N 78
# define W 87
# define S 83
# define E 69

typedef struct s_coor_i
{
	int	x;
	int	y;
}	t_coor_i;


typedef struct s_coor_f
{
	float	x;
	float	y;
}	t_coor_f;

typedef struct s_ray
{
	t_coor_f		hit_point;
	t_coor_i		cell;
	double			length;
	double			perp_wall_dist;
	int				hit_side;
	double			angle;
	t_coor_f		ray_dir;
}	t_ray;

typedef struct s_text
{
	void	*text;
	int		text_w;
	int		text_h;
	char	*text_adr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_text;

typedef struct s_config
{
	int			fd;
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	t_list		*map_list;
	char		**map;
	char		*map_tmp;
	int			map_size;
	int			map_row;
    char        **text_paths;
}	t_config;

typedef struct s_player
{
	t_coor_f	coordinate;
	// t_coor_f	t_left;
	// t_coor_f	t_right;
	// t_coor_f	b_left;
	// t_coor_f	b_right;
	t_coor_f	dir;
    t_coor_i	view_dst_pos;
	float		angle;
	int			ori;
}	t_player;

typedef struct s_image
{
	void		*img;
	char		*img_addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}	t_image;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_image		*mini_map_border;
	t_image		*mini_map;
	t_image		*player;
	t_image		*window;
}	t_mlx;

typedef struct s_data
{
    /* Config from .cub file */
	t_config	config;
    
    /* Mlx */
	t_mlx		mlx;
    int         cell_size;

    /* Player */
	t_player	player;
    double      move_speed;
    double      rot_speed;

    /* Vision */
    int         fov;
    int         view_dst;
    int         ray_nb;
	t_ray		*rays;

    /* Keyboard */
    int		    keyboard[200];

    /* Floor and ceiling */
    int         floor_color;
	int         ceiling_color;

    /* Textures */
    t_text      *textures;
	
}	t_data;



#endif
