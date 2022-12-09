/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:33:35 by vcart             #+#    #+#             */
/*   Updated: 2022/12/09 15:59:39 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

t_complex	place_c(double x, double y, int length, int width, t_map *map)
{
	t_complex	x_vect;
	t_complex	y_vect;
	t_complex	zoom;

	x_vect = (t_complex){-2, 2};
	y_vect = (t_complex){-2,  2};
	zoom = (t_complex){length / (x_vect.y - x_vect.x) * map->zoom_factor, width / (y_vect.y - y_vect.x) * map->zoom_factor};
	return ((t_complex){(x / zoom.x + x_vect.x) + map->move_x, (y  / zoom.y + y_vect.x) + map->move_y});
}

int	mandelbrot_calculator(t_complex z, t_complex c, int max_i)
{
	int			i;
	double		temp;

	i = 0;
	while ((z.x * z.x) + (z.y * z.y) < 4 && i < max_i)
	{
		temp = z.x;
		z = (t_complex){(z.x * z.x - z.y * z.y) + c.x, (2 * z.y * temp) + c.y};
		i++;
	}
	return (i);
}

void	mandelbrot_generator(t_data *data, t_map *map)
{
	t_complex	z;
	t_complex	c;
	int			i;
	double		x;
	double		y;

	y = 0;
	while (y < map->width)
	{
		x = 0;
		while (x < map->length)
		{
			z = (t_complex){0, 0};
			c = place_c(x, y, map->length, map->width, map);
			i = mandelbrot_calculator(z, c, map->max_i);
			if (i == map->max_i)
				opti_pixelput(data, x, y, 0x00000000);
			else
				opti_pixelput(data, x, y, create_trgb(0, i * 180 / map->max_i, 0, 0));
			x++;
		}
		y++;
	}
}
