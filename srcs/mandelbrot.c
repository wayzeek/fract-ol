/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:33:35 by vcart             #+#    #+#             */
/*   Updated: 2022/12/08 14:31:10 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

#include <stdio.h>

void	mandelbrot_generator(t_data *data, int max_iteration, int length, int width)
{
	t_complex	z;
	t_complex	c;
	int			i;
	double		x;
	double		y;
	double		temp;
	double			x1 = -2.1;
	double			x2 = 0.6;
	double			y1 = -1.2;
	double			y2 = 1.2;
	double			zoom_x = length / (x2 - x1);
	double			zoom_y = width / (y2 - y1);

	y = 0;
	while (y < width)
	{
		x = 0;
		while (x < length)
		{
			z = (t_complex){0, 0};
			c = (t_complex){x / zoom_x + x1, y / zoom_y + y1};
			i = 0;
			while ((z.x * z.x) + (z.y * z.y) < 4 && i < max_iteration)
			{
				temp = z.x;
				z = (t_complex){(z.x * z.x - z.y * z.y) + c.x, (2 * z.y * temp) + c.y};
				i++;
			}
			if (i == max_iteration)
				opti_pixelput(data, x, y, 0x000000);
			else
				opti_pixelput(data, x, y, i * 0xfcba03/ max_iteration);
			x++;
		}
		y++;
	}
}
