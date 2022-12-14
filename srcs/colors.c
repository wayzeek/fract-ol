/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:42:08 by vcart             #+#    #+#             */
/*   Updated: 2022/12/14 09:55:27 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r  << 16 | g << 8 | b);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	fade(int trgb_start, int trgb_end, double point)
{
	int	r;
	int	g;
	int	b;

	//printf("ratio : %f\n", point);
	r = (get_r(trgb_start) - get_r(trgb_end)) * point + get_r(trgb_end);
	g = (get_g(trgb_start) - get_g(trgb_end)) * point + get_g(trgb_end);
	b = (get_b(trgb_start) - get_b(trgb_end)) * point + get_b(trgb_end);
	return (create_trgb(0, r, g, b));
}
