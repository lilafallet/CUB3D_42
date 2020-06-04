/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 10:20:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/04 11:01:11 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	left_or_right(t_graph *gr)
{
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
	{
		gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->mv.comb_posx
							- gr->rting.diry * SPEED_MV : gr->mv.comb_posx
							+ gr->rting.diry * SPEED_MV;
		gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->mv.comb_posy
							+ gr->rting.dirx * SPEED_MV : gr->mv.comb_posy
							- gr->rting.dirx * SPEED_MV;
	}
	else
	{
		gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->rting.posx
							- gr->rting.diry * SPEED_MV : gr->rting.posx
							+ gr->rting.diry * SPEED_MV;
		gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->rting.posy
							+ gr->rting.dirx * SPEED_MV : gr->rting.posy
							- gr->rting.dirx * SPEED_MV;
	}
}

void	up_or_down(t_graph *gr)
{
	gr->mv.new_posx = gr->mv.log & MV_UP ? gr->rting.posx + gr->rting.dirx
						* SPEED_MV : gr->rting.posx - gr->rting.dirx
						*SPEED_MV;
	gr->mv.new_posy = gr->mv.log & MV_UP ? gr->rting.posy + gr->rting.diry
						* SPEED_MV : gr->rting.posy - gr->rting.diry
						*SPEED_MV;
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
