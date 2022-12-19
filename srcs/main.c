/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:27:25 by vcart             #+#    #+#             */
/*   Updated: 2022/12/19 13:49:58 by vcart            ###   ########.fr       */
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

void	fill_map(t_map	*map)
{
	map->move_x = 0;
	map->move_y = 0;
	map->length = 1000;
	map->width = 1000;
	map->max_i = 50;
	map->zoom_factor = 1;
	map->mlx = mlx_init();
	map->mlx_win = mlx_new_window(map->mlx, map->length, map->width,
			"fract_ol");
	map->img.img = mlx_new_image(map->mlx, 1000, 1000);
	map->img.addr = mlx_get_data_addr(map->img.img, &map->img.bits_per_pixel,
			&map->img.line_length, &map->img.endian);
}

int	check_args(int argc, char **argv, t_map *map)
{
	if (argc != 2)
	{
		ft_putstr("[ERROR]\nThe number of parameter is incorrect.\nPlease\
		choose between the Mandelbrot set [m] and the Julia set [j].\n");
		return (-1);
	}
	if (argv[1][0] == 'm')
		map->fractal_chosen = 'm';
	else if (argv[1][0] == 'j')
	{
		map->fractal_chosen = 'j';
		map->julia_x = -0.4;
		map->julia_y = 0.6;
	}
	else if (argv[1][0] != 'j' || argv[1][0] != 'm')
	{
		ft_putstr("[ERROR]\nThe parameter given is incorrect.\nPlease\
		choose between the Mandelbrot set [m] and the Julia set [j].\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (check_args(argc, argv, &map) == -1)
		return (-1);
	fill_map(&map);
	threading(&map);
	mlx_hook(map.mlx_win, ON_MOUSEDOWN, 27, &mouse_check, &map);
	mlx_hook(map.mlx_win, ON_DESTROY, 0, &quit_window, &map);
	mlx_key_hook(map.mlx_win, &check_key, &map);
	mlx_loop(map.mlx);
	return (0);
}
