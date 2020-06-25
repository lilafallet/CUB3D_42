/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:16:55 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:16:56 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int			get_init_offset(const int size, const int max)
{
	static int init_offset = UNDEFINED;

	if (init_offset == UNDEFINED)
		init_offset = size * MAP_OFFSET / max;
	return (init_offset);
}

int			get_final_color(const int i, const int j, const int color)
{
	if (color == GREEN && (i < SIZEMIN_SPRITE || j < SIZEMIN_SPRITE
					|| i > SIZEMAX_SPRITE || j > SIZEMAX_SPRITE))
		return (GREY);
	else if (color == RED && (i < SIZEMIN_PLAYER || j < SIZEMIN_PLAYER
					|| i > SIZEMAX_PLAYER || j > SIZEMAX_PLAYER))
		return (GREY);
	return (color);
}
