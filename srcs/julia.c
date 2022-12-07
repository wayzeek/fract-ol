/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:30:22 by vcart             #+#    #+#             */
/*   Updated: 2022/12/07 15:01:32 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

void	julia_generator(t_data *data, t_vect *c, int max_iteration)
{
	t_vect	*z;
	int		i;

	z->x = 0;
	z->y = 0;
	i = 0;
	while (i < max_iteration)
	{
		z->x = (z->x * z->x - z->y * z->y) + c->x;
		z->y = (2 * (z->x * z->y)) + c->y;
		if (z->x * z->x - z->y * z->y > 4)
			opti_pixelput(data, z, i / max_iteration);
		else
			opti_pixelput(data, z, 0x000000);
		i++;
	}
}
