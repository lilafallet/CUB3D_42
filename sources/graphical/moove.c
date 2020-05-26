/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 10:20:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/26 18:45:44 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	look_right(t_graph *gr, double tmp_dirx, double tmp_planecamx)
{
	gr->rting.dirx = gr->rting.dirx * cos(SPEED_LK) - gr->rting.diry
						* sin(SPEED_LK);
	gr->rting.diry = tmp_dirx * sin(SPEED_LK) + gr->rting.diry
						* cos(SPEED_LK);
	gr->rting.planecamx = gr->rting.planecamx * cos(SPEED_LK)
							- gr->rting.planecamy * sin(SPEED_LK);
	gr->rting.planecamy = tmp_planecamx * sin(SPEED_LK)
							+ gr->rting.planecamy * cos(SPEED_LK);

}

static void	look_left(t_graph *gr, double tmp_dirx, double tmp_planecamx)
{
	gr->rting.dirx = gr->rting.dirx * cos(-SPEED_LK) - gr->rting.diry
						* sin(-SPEED_LK);
	gr->rting.diry = tmp_dirx * sin(-SPEED_LK) + gr->rting.diry
						* cos(-SPEED_LK);
	gr->rting.planecamx = gr->rting.planecamx * cos(-SPEED_LK)
							- gr->rting.planecamy * sin(-SPEED_LK);
	gr->rting.planecamy = tmp_planecamx * sin(-SPEED_LK)
							+ gr->rting.planecamy * cos(-SPEED_LK);
}

static void	moove_up_down(t_graph *gr)
{
	gr->mv.new_posx = gr->mv.log & MV_UP ? gr->rting.posx + gr->rting.dirx
						* SPEED_MV : gr->rting.posx - gr->rting.dirx
						*SPEED_MV;
	gr->mv.new_posy = gr->mv.log & MV_UP ? gr->rting.posy + gr->rting.diry
						* SPEED_MV : gr->rting.posy - gr->rting.diry
						*SPEED_MV;
}

static void	moove_left_right(t_graph *gr)
{
	gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->rting.posx
						- gr->rting.diry * SPEED_MV : gr->rting.posx
						+ gr->rting.diry * SPEED_MV;
	gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->rting.posy
						+ gr->rting.dirx * SPEED_MV : gr->rting.posy
						- gr->rting.dirx * SPEED_MV;
}

int	moove(t_graph *gr)
{
	t_map	*map;
	double	tmp_dirx;
	double	tmp_planecamx;
	
	tmp_dirx = gr->rting.dirx;
	tmp_planecamx = gr->rting.planecamx;
	map = get_map(NULL);
	gr->rting.mv_update = FALSE;
	if (gr->mv.log & LK_RIGHT || gr->mv.log & LK_LEFT)
		gr->mv.log & LK_RIGHT ? look_right(gr, tmp_dirx, tmp_planecamx)
									: look_left(gr, tmp_dirx, tmp_planecamx);	
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
		moove_up_down(gr);
	if (gr->mv.log & MV_RIGHT || gr->mv.log & MV_LEFT)
		moove_left_right(gr);
	if (is_wall(gr, map) == FALSE && gr->mv.log & PRESS
								&& (gr->mv.log & RELEASE) == FALSE)
			gr->rting.mv_update = TRUE;
	if (gr->rting.mv_update == TRUE && gr->mv.log & PRESS
			&& (gr->rting.posx != gr->mv.new_posx
			|| gr->rting.posy != gr->mv.new_posy))
	{
		gr->rting.posx = gr->mv.new_posx;
		gr->rting.posy = gr->mv.new_posy;
		init_graph(gr, map);
		process_window(gr);	
	}
	return (SUCCESS);
}
