/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:52:06 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 18:01:39 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_graph *gr, t_map *map)
{
	if (is_posy_into_wall(gr, map) == TRUE)
		gr->mv.new_posy = gr->mv.old_posy;
	if (is_posx_into_wall(gr, map) == TRUE)
		gr->mv.new_posx = gr->mv.old_posx;
	return (FALSE);
}

int		update(t_graph *gr)
{
	return (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN || gr->mv.log & MV_LEFT
			|| gr->mv.log & MV_RIGHT || gr->mv.log & LK_LEFT
			|| gr->mv.log & LK_RIGHT ? TRUE : FALSE);
}

void	pos(t_graph *gr, size_t x, size_t y)
{
	gr->sp.pos[gr->sp.count].x = x + 0.5;
	gr->sp.pos[gr->sp.count].y = y + 0.5;
}

t_graph	*gr_holder(t_graph *gr)
{
	static t_graph	*gr_keep;

	if (gr_keep == NULL && gr != NULL)
		gr_keep = gr;
	return (gr_keep);
}

int		get_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
