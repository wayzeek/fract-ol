/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:27:25 by vcart             #+#    #+#             */
/*   Updated: 2022/12/16 13:54:04 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

#include <stdio.h>

void	opti_pixelput(t_data *data, double x, double y, int color)
{
	char	*dst;

	dst = data->addr + (int)(y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	check_key(int key_code, t_map *map)
{
	if (key_code == 126)
		map->move_y -= 0.5 / map->zoom_factor;
	else if (key_code == 125)
		map->move_y += 0.5 / map->zoom_factor;
	else if (key_code == 124)
		map->move_x += 0.5 / map->zoom_factor;
	else if (key_code == 123)
		map->move_x -= 0.5 / map->zoom_factor;
	else if (key_code == 69)
	{
		map->zoom_factor += 0.05 * map->zoom_factor;
	}
	else if (key_code == 78)
		map->zoom_factor -= 0.05 * map->zoom_factor;
	threading(map);
	return (0);
}

int	check_mouse(int key_code, int x, int y, t_map *map)
{
	
	double	x_pos;
	double	y_pos;

	x_pos = (x - map->length / 2) / (map->zoom_factor * 100);
	y_pos = (y - map->width / 2) / (map->zoom_factor * 100);
	
	if (key_code == 4)
	{
		map->move_x += (0.05 * x_pos);
		map->move_y += (0.05 * y_pos);
		map->zoom_factor *= 1.05;
		threading(map);
	}
	else if (key_code == 5)
	{
		map->zoom_factor /= 1.2;
		map->move_x -= 0.1 * x_pos;
		map->move_y -= 0.1 * y_pos;
		threading(map);
	}
	else if (key_code == 2)
	{
		map->move_x = 0;
		map->move_y = 0;
		map->zoom_factor = 1;
		threading(map);
	}
	return (0);
}

int	main(void)
{
	t_map	map;

	map.move_x = 0;
	map.move_y = 0;
	map.length = 1000;
	map.width = 1000;
	map.max_i = 50;
	map.zoom_factor = 1;
	map.mlx = mlx_init();
	map.mlx_win = mlx_new_window(map.mlx, map.length, map.width, "Mandelbrot");
	map.img.img = mlx_new_image(map.mlx, 1000, 1000);
	map.img.addr = mlx_get_data_addr(map.img.img, &map.img.bits_per_pixel,
			&map.img.line_length, &map.img.endian);
	threading(&map);
	mlx_hook(map.mlx_win, ON_MOUSEDOWN, 27, &check_mouse, &map);
	mlx_key_hook(map.mlx_win, &check_key, &map);
	mlx_loop(map.mlx);
}
