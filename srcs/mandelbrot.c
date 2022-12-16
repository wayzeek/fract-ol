/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:33:35 by vcart             #+#    #+#             */
/*   Updated: 2022/12/16 13:57:44 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

t_complex	place_c(double x, double y, int length, int width, t_map *map)
{
	t_complex	zoom;

	map->x_vect = (t_complex){-2 * (1 / map->zoom_factor), 2};
	map->y_vect = (t_complex){-2 * (1 / map->zoom_factor),  2};
	zoom = (t_complex){length / (map->x_vect.y - map->x_vect.x) * map->zoom_factor, width / (map->y_vect.y - map->y_vect.x) * map->zoom_factor};
	return ((t_complex){(x / zoom.x + map->x_vect.x) + map->move_x, (y  / zoom.y + map->y_vect.x) + map->move_y});
}

int	mandelbrot_calculator(t_complex z, t_complex c, int max_i)
{
	int			i;
	double		temp;

	i = 0;
	while ((z.x * z.x) + (z.y * z.y) < 4 && i < max_i)
	{
		temp = z.x;
		z = (t_complex){(z.x * z.x - z.y * z.y) - 1, (2 * z.y * temp) + 0};
		i++;
	}
	return (i);
}

void	mandelbrot_generator(t_thread *t)
{
	t_complex	z;
	t_complex	c;
	int			i;
	double		x;
	double		y;

	y = t->map->width / 8 * t->i;
	while (y < t->map->width / 8 * (t->i + 1))
	{
		x = 0;
		while (x < t->map->length)
		{
			z.x = (t->map->move_x + (x - t->map->length / 2)) / (t->map->zoom_factor * 100);
			z.y = (t->map->move_y + (y - t->map->width / 2)) / (t->map->zoom_factor * 100);
			//printf("map.move.x = %f map.move_y = %f\n", t->map->move_x, t->map->move_y);
			//printf("x = %f y = %f\n", x, y);
			//printf("z.x = %f z.i = %f\n\n", z.x, z.y);
			c = place_c(x, y, t->map->length, t->map->width, t->map);
			i = mandelbrot_calculator(c, c, t->map->max_i);
			if (i == t->map->max_i)
				opti_pixelput(&t->map->img, x, y, 0x00000000);
			else
				opti_pixelput(&t->map->img, x, y, fade(0x00FFF01F, 0x00292444, i / t->map->max_i));
			x++;
		}
		y++;
	}
}

void	threading(t_map *map)
{
	int			i;
	t_thread	threads[8];

	i = 0;
	mlx_clear_window(map->mlx, map->mlx_win);
	while (i < 8)
	{
		threads[i].i = i;
		threads[i].map = map;
		pthread_create(&threads[i].thread, NULL, (void *)mandelbrot_generator, &threads[i]);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		pthread_join(threads[i].thread, NULL);
		i++;
	}
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img.img, 0, 0);
}
