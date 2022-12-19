/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:48:26 by vcart             #+#    #+#             */
/*   Updated: 2022/12/19 14:07:48 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <math.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include "./mlx/mlx.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_complex {
	double	x;
	double	y;
}			t_complex;

typedef struct s_map {
	void		*mlx;
	void		*mlx_win;
	double		max_i;
	int			length;
	int			width;
	t_complex	x_vect;
	t_complex	y_vect;
	double		zoom_factor;
	double		move_x;
	double		move_y;
	char		fractal_chosen;
	double		julia_x;
	double		julia_y;
	t_data		img;
}			t_map;

typedef struct s_thread
{
	t_map		*map;
	int			i;
	pthread_t	thread;
}				t_thread;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

void		opti_pixelput(t_data *data, double x, double y, int color);
void		fractal_generator(t_thread *t);
t_complex	place_c(double x, double y, t_map *map);
int			create_trgb(int t, int r, int g, int b);
int			fade(int trgb_start, int trgb_end, double point);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
void		threading(t_map *map);
int			quit_window(t_map *map);
int			check_key(int key_code, t_map *map);
int			mouse_check(int key_code, int x, int y, t_map *map);
int			mouse_scroll_down(double x_pos, double y_pos, t_map *map);
int			mouse_click_right(t_map *map);
void		ft_putchar(char c);
void		ft_putstr(char *str);
void		put_color(int i, double x, double y, t_map *map);

#endif