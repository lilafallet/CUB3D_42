/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 10:20:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/22 18:52:40 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	moove(t_graph *gr)
{
	t_map	*map;

	map = get_map(NULL);
	gr->rting.mv_update = FALSE;
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
	{
		gr->rting.mv_update = TRUE;
		ft_printf("MV_UP || MV_DOWN\n");
		gr->rting.posx = gr->rting.posx + gr->rting.dirx * SPEED
							* gr->mv.mv_dir;
		gr->rting.posy = gr->rting.posy + gr->rting.diry * SPEED
							* gr->mv.mv_dir;
	}
	else if (gr->mv.log & MV_RIGHT || gr->mv.log & MV_LEFT)
	{
		gr->rting.mv_update = TRUE;
		ft_printf("MV_RIGHT || MV_LEFT\n");
		gr->rting.posx = gr->mv.log & MV_RIGHT ? gr->rting.posx
							- gr->rting.diry * SPEED : gr->rting.posx
							+ gr->rting.diry * SPEED;
		gr->rting.posy = gr->mv.log & MV_RIGHT ? gr->rting.posy
							+ gr->rting.dirx * SPEED : gr->rting.posy
							+ gr->rting.dirx * SPEED;
	}
	//else if (gr->mv.log & LOOK_RIGHT || gr->mov.log & LOOK_LEFT)
	if (gr->rting.mv_update == TRUE)
	{
		init_graph(gr, map);
		process_window(gr);	
	}
	return (SUCCESS);
}
