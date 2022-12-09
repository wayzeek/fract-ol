/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:27:25 by vcart             #+#    #+#             */
/*   Updated: 2022/12/09 16:37:57 by vcart            ###   ########.fr       */
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

int	render_next_frame(t_map *map)
{
	map->img.img = mlx_new_image(map->mlx, 1000, 1000);
	map->img.addr = mlx_get_data_addr(map->img.img, &map->img.bits_per_pixel,
			&map->img.line_length, &map->img.endian);
	mandelbrot_generator(&map->img, map);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img.img, 0, 0);
	mlx_destroy_image(map->mlx, map->img.img);
	return (0);
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
		map->zoom_factor += 0.5 * map->zoom_factor;
	else if (key_code == 78)
		map->zoom_factor -= 0.5 * map->zoom_factor;
	return (0);
}

int	check_mouse(int key_code, t_map *map)
{
	if (key_code == 4)
		map->zoom_factor += 0.5;
	else if (key_code == 5)
		map->zoom_factor -= 0.5;
	else if (key_code == 2)
	{
		map->move_x = 0;
		map->move_y = 0;
		map->zoom_factor = 1;
	}
	return (0);
}

int	main(int argc, char **argv)
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
	mlx_loop_hook(map.mlx, render_next_frame, &map);
	mlx_mouse_hook(map.mlx_win, check_mouse, &map);
	mlx_key_hook(map.mlx_win, &check_key, &map);
	mlx_loop(map.mlx);
}