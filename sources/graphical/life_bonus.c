/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:16:37 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:16:38 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		trace_rectangle(t_graph *gr, t_map *map, t_set_point set,
							const int color)
{
	int		x;
	int		y;

	y = set.a.y;
	while (y < set.b.y)
	{
		x = set.a.x;
		while (x < set.b.x)
		{
			gr->win.data[y * map->recup.resolution[AXE_X] + x] = color;
			x++;
		}
		y++;
	}
}

t_set_point	set_point(int ax, int ay, int bx, int by)
{
	t_set_point set;

	set.a.x = ax;
	set.b.x = bx;
	set.a.y = ay;
	set.b.y = by;
	return (set);
}

void		life(t_graph *gr, t_map *map)
{
	t_set_point		set;
	static int		x_life = MAX_LIFEBAR;

	if (gr->lf.count_outsprite == 1)
		gr->lf.count++;
	if (gr->lf.count > 0 && gr->lf.count_outsprite == TRUE
			&& (gr->lf.count != END_LIFE && gr->lf.count_outsprite == TRUE))
		x_life -= DIMINUTION_LIFE;
	set = set_point(ENDX_EXT, STARTX_EXT, ENDY_EXT, STARTY_EXT);
	trace_rectangle(gr, map, set, gr->lf.count < LIGHT ? WHITE : RED);
	set = set_point(ENDX, STARTX, MAX_LIFEBAR, STARTY);
	trace_rectangle(gr, map, set, RED);
	set = set_point(ENDX, STARTX, x_life, STARTY);
	trace_rectangle(gr, map, set, GREEN_LIFE);
	if (gr->lf.count == DEAD || x_life == ENDX)
	{
		gr->lf.count = DEAD + 1;
		x_life = MAX_LIFEBAR;
		process_window(gr);
	}
}
