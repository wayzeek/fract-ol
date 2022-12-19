/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:27:27 by vcart             #+#    #+#             */
/*   Updated: 2022/12/19 13:59:55 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	put_color(int i, double x, double y, t_map *map)
{
	if (i == map->max_i)
		opti_pixelput(&map->img, x, y, 0);
	else
		opti_pixelput(&map->img, x, y, \
		fade(0x00FFF01F, 0x00292444, i / map->max_i));
}
