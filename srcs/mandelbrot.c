/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:33:35 by vcart             #+#    #+#             */
/*   Updated: 2022/12/20 14:45:29 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

t_complex	place_c(double x, double y, t_map *map)
{
	t_complex	zoom;

	map->x_vect = (t_complex){-2 * (1 / map->zoom_factor), 2};
	map->y_vect = (t_complex){-2 * (1 / map->zoom_factor), 2};
	zoom = (t_complex){map->length / (map->x_vect.y - map->x_vect.x) \
	* map->zoom_factor, map->width / (map->y_vect.y - map->y_vect.x) \
	* map->zoom_factor};
	return ((t_complex){(x / zoom.x + map->x_vect.x) + map->move_x, \
	(y / zoom.y + map->y_vect.x) + map->move_y});
}

double	mandelbrot_calculator(t_complex z, t_complex c, int max_i)
{
	double		i;
	double		temp;

	i = 0;
	while ((z.x * z.x) + (z.y * z.y) <= 4 && i < max_i)
	{
		temp = z.x;
		z = (t_complex){(z.x * z.x - z.y * z.y) + c.x, (2 * z.y * temp) + c.y};
		i++;
	}
	return (i);
}

double	julia_calculator(t_complex c, t_map *map)
{
	double		i;
	double		temp;

	i = 0;
	while ((c.x * c.x) + (c.y * c.y) <= 4 && i < map->max_i)
	{
		temp = c.x;
		c = (t_complex){(c.x * c.x - c.y * c.y) + map->julia_x, \
		(2 * c.y * temp) + map->julia_y};
		i++;
	}
	return (i);
}

void	fractal_generator(t_thread *t)
{
	t_complex	c;
	double		i;
	double		x;
	double		y;

	y = t->map->width / 8 * t->i;
	while (y < t->map->width / 8 * (t->i + 1))
	{
		x = 0;
		while (x++ < t->map->length)
		{
			c = place_c(x, y, t->map);
			if (t->map->fractal_chosen == 'm')
				i = mandelbrot_calculator(c, c, t->map->max_i);
			else if (t->map->fractal_chosen == 'j')
				i = julia_calculator(c, t->map);
			put_color(i, x, y, t->map);
		}
		y++;
	}
}

void	threading(t_map *map)
{
	int			i;
	t_thread	threads[8];

	i = 0;
	while (i < 8)
	{
		threads[i].i = i;
		threads[i].map = map;
		pthread_create(&threads[i].thread, NULL, \
		(void *)fractal_generator, &threads[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i].thread, NULL);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img.img, 0, 0);
}
