/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:16:58 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:16:59 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		is_wall(t_graph *gr, t_map *map)
{
	gr->lf.sprite = FALSE;
	gr->lf.count_outsprite = FALSE;
	if (is_sprite(gr, map, gr->mv.new_posy, gr->mv.new_posx) == TRUE)
	{
		gr->lf.sprite = TRUE;
		screen_life(gr, map);
		gr->lf.count_outsprite++;
	}
	if (is_posy_into_wall(gr, map) == TRUE)
		gr->mv.new_posy = gr->mv.old_posy;
	if (is_posx_into_wall(gr, map) == TRUE)
		gr->mv.new_posx = gr->mv.old_posx;
	return (FALSE);
}

void	left_or_right(t_graph *gr)
{
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
	{
		gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->mv.comb_posx
						- gr->rting.diry * gr->mv.speed_mv
						: gr->mv.comb_posx + gr->rting.diry * gr->mv.speed_mv;
		gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->mv.comb_posy
						+ gr->rting.dirx * gr->mv.speed_mv : gr->mv.comb_posy
						- gr->rting.dirx * gr->mv.speed_mv;
	}
	else
	{
		gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->rting.posx
							- gr->rting.diry * gr->mv.speed_mv : gr->rting.posx
							+ gr->rting.diry * gr->mv.speed_mv;
		gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->rting.posy
							+ gr->rting.dirx * gr->mv.speed_mv : gr->rting.posy
							- gr->rting.dirx * gr->mv.speed_mv;
	}
}

void	up_or_down(t_graph *gr)
{
	gr->mv.new_posx = gr->mv.log & MV_UP ? gr->rting.posx + gr->rting.dirx
						* gr->mv.speed_mv : gr->rting.posx - gr->rting.dirx
						* gr->mv.speed_mv;
	gr->mv.new_posy = gr->mv.log & MV_UP ? gr->rting.posy + gr->rting.diry
						* gr->mv.speed_mv : gr->rting.posy - gr->rting.diry
						* gr->mv.speed_mv;
	if (gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT)
	{
		gr->mv.comb_posx = gr->mv.new_posx;
		gr->mv.comb_posy = gr->mv.new_posy;
	}
}

void	moove_up_down(t_graph *gr)
{
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
		up_or_down(gr);
	if (gr->mv.log & MV_UP && gr->mv.log & MV_DOWN)
	{
		gr->mv.new_posx = gr->rting.posx;
		gr->mv.new_posy = gr->rting.posy;
	}
}

void	moove_left_right(t_graph *gr)
{
	if (gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT)
		left_or_right(gr);
	if (gr->mv.log & MV_LEFT && gr->mv.log & MV_RIGHT)
	{
		gr->mv.new_posx = gr->rting.posx;
		gr->mv.new_posy = gr->rting.posy;
	}
}
