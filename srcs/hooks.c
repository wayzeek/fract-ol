/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:25:41 by vcart             #+#    #+#             */
/*   Updated: 2022/12/19 14:00:11 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

int	quit_window(t_map *map)
{
	mlx_destroy_image(map->mlx, map->img.img);
	mlx_destroy_window(map->mlx, map->mlx_win);
	exit(0);
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
		map->zoom_factor += 0.05 * map->zoom_factor;
	else if (key_code == 78)
		map->zoom_factor -= 0.05 * map->zoom_factor;
	else if (key_code == 53)
		quit_window(map);
	threading(map);
	return (0);
}

int	mouse_check(int key_code, int x, int y, t_map *map)
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
		mouse_scroll_down(x_pos, y_pos, map);
	else if (key_code == 2)
		mouse_click_right(map);
	return (0);
}

int	mouse_scroll_down(double x_pos, double y_pos, t_map *map)
{
	map->move_x += (0.05 * x_pos);
	map->move_y += (0.05 * y_pos);
	map->zoom_factor /= 1.05;
	threading(map);
	return (0);
}

int	mouse_click_right(t_map *map)
{
	map->move_x = 0;
	map->move_y = 0;
	map->zoom_factor = 1;
	threading(map);
	return (0);
}
