/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:22:33 by alorain           #+#    #+#             */
/*   Updated: 2022/07/06 15:27:58 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_img *data, t_point p, int color)
{
	char	*dst;

	if (p.x <= W_WIDTH && p.x >= 0 && p.y >= 0 && p.y <= W_HEIGHT)
	{
		dst = data->addr + (p.y * data->size_l + p.x
				* (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	swap_coordinates(t_point *p1, t_point *p2)
{
	int	temp;

	temp = p1->x;
	p1->x = p2->x;
	p2->x = temp;
	temp = p1->y;
	p1->y = p2->y;
	p2->y = temp;
}
