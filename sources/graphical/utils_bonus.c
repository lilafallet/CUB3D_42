/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:17:35 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:17:37 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		is_sprite(t_graph *gr, t_map *map, double y, double x)
{
	const double pad = gr->mv.speed_mv + 0.06;

	if ((int)y - pad < 0 || (size_t)y + pad > map->utils.max_line)
		return (FALSE);
	if ((int)x - pad < 0 || (size_t)x + pad > map->utils.max_index - 1)
		return (FALSE);
	return (map->recup.tab_map[(int)(y)][(int)(x)] == SPRITE
		|| map->recup.tab_map[(int)(y + pad)][(int)(x)] == SPRITE
		|| map->recup.tab_map[(int)(y - pad)][(int)(x)] == SPRITE
		|| map->recup.tab_map[(int)(y)][(int)(x + pad)] == SPRITE
		|| map->recup.tab_map[(int)(y)][(int)(x - pad)] == SPRITE
		|| map->recup.tab_map[(int)(y - pad)][(int)(x - pad)] == SPRITE
		|| map->recup.tab_map[(int)(y + pad)][(int)(x + pad)] == SPRITE
		|| map->recup.tab_map[(int)(y + pad)][(int)(x - pad)] == SPRITE
		|| map->recup.tab_map[(int)(y - pad)][(int)(x + pad)] == SPRITE);
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
