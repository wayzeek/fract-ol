/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:48:26 by vcart             #+#    #+#             */
/*   Updated: 2022/12/09 15:46:01 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <math.h>
# include "./minilibx/mlx.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_complex {
	double	x;
	double	y;
}				t_complex;

typedef struct s_map {
	void	*mlx;
	void	*mlx_win;
	int		max_i;
	int		length;
	int		width;
	double	zoom_factor;
	double	move_x;
	double	move_y;
	t_data	img;
}			  t_map;

void	opti_pixelput(t_data *data, double x, double y, int color);
void	mandelbrot_generator(t_data *data, t_map *map);
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

#endif