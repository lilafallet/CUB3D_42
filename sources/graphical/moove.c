/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 10:20:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/24 20:36:57 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	moove(t_graph *gr)
{
	t_map	*map;

	map = get_map(NULL);
	gr->rting.mv_update = FALSE;
	if (gr->mv.log & LK_RIGHT || gr->mv.log & LK_LEFT)
	{
		ft_printf("LOOK RIGHT || LOOK RIGHT\n"); //
		gr->mv.degree_lk = gr->mv.lk_dir * SPEED_LK;
		gr->mv.radius_lk = gr->mv.degree_lk / DEGREE * M_PI;
		gr->mv.new_dirx = cos(gr->mv.radius_lk) * gr->rting.posx
								- sin(gr->mv.radius_lk) * gr->rting.posy; 
		gr->mv.new_diry = sin(gr->mv.radius_lk) * gr->rting.posx
								+ cos(gr->mv.radius_lk) * gr->rting.posy;
		gr->rting.posx = gr->mv.new_dirx;
		gr->rting.posy = gr->mv.new_diry;
		gr->mv.new_dirx = 0;
		gr->mv.new_diry = 0;
		gr->mv.new_planecamx = cos(gr->mv.radius_lk) * gr->rting.posx
								- sin(gr->mv.radius_lk) * gr->rting.posy; 
		gr->mv.new_planecamy = sin(gr->mv.radius_lk) * gr->rting.posx
								+ cos(gr->mv.radius_lk) + gr->rting.posy;
		gr->rting.posx = gr->mv.new_planecamx;
		gr->rting.posy = gr->mv.new_planecamy;
		gr->mv.new_planecamx = 0;
		gr->mv.new_planecamy = 0;
		init_graph(gr, map);
		process_window(gr);	
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
