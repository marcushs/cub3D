/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_class.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:14:03 by tduprez           #+#    #+#             */
/*   Updated: 2023/10/04 18:27:08 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CLASS_H
# define MLX_CLASS_H

# include "../../minilibx-linux/mlx.h"
# include <stdlib.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
}	t_mlx;

void	mlx_destructor(t_mlx *mlx);

#endif
