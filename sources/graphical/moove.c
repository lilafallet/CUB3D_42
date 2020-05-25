/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 10:20:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/25 15:43:54 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	moove(t_graph *gr)
{
	t_map	*map;
	double	tmp_dirx;
	double	tmp_planecamx;

	map = get_map(NULL);
	gr->rting.mv_update = FALSE;
	tmp_dirx = gr->rting.dirx;
	tmp_planecamx = gr->rting.planecamx;
	if (gr->mv.log & LK_RIGHT || gr->mv.log & LK_LEFT)
	{
		if (gr->mv.log & LK_LEFT)
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
		else if (gr->mv.log & LK_RIGHT)
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
	}
	else if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
	{
		gr->mv.new_posx = gr->rting.posx + gr->rting.dirx * SPEED_MV
							* gr->mv.mv_dir;
		gr->mv.new_posy = gr->rting.posy + gr->rting.diry * SPEED_MV
							* gr->mv.mv_dir;
	}
	else if (gr->mv.log & MV_RIGHT || gr->mv.log & MV_LEFT)
	{
		gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->rting.posx
							- gr->rting.diry * SPEED_MV : gr->rting.posx
							+ gr->rting.diry * SPEED_MV;
		gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->rting.posy
							+ gr->rting.dirx * SPEED_MV : gr->rting.posy
							- gr->rting.dirx * SPEED_MV;
	}
	if (is_wall(gr, map) == FALSE)
			gr->rting.mv_update = TRUE;
	if (gr->rting.mv_update == TRUE)
	{
		ft_printf("HELLO\n"); //
		gr->rting.posx = gr->mv.new_posx;
		gr->rting.posy = gr->mv.new_posy;
		init_graph(gr, map);
		process_window(gr);	
	}
	return (SUCCESS);
}
