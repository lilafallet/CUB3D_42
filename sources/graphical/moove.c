/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 10:20:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/22 17:16:36 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	moove(t_graph *gr)
{
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
	{
		ft_printf("MV_UP || MV_DOWN\n");
		gr->mv.new_posx = gr->rting.posx + gr->rting.dirx * SPEED
							* gr->mv.mv_dir;
		gr->mv.new_posy = gr->rting.posy + gr->rting.diry * SPEED
							* gr->mv.mv_dir;
	}
	else if (gr->mv.log & MV_RIGHT || gr->mv.log & MV_LEFT)
	{
		ft_printf("MV_RIGHT || MV_LEFT\n");
		gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->rting.posx
							- gr->rting.diry * SPEED : gr->rting.posx
							+ gr->rting.diry * SPEED;
		gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->rting.posy
							+ gr->rting.dirx * SPEED : gr->rting.posy
							+ gr->rting.dirx * SPEED;
	}
	//else if (gr->mv.log & LOOK_RIGHT || gr->mov.log & LOOK_LEFT)
	return (SUCCESS);
}
