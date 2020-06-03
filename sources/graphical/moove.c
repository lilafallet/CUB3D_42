/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 10:20:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/03 15:19:31 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	moove_up_down(t_graph *gr)
{
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
	{
		//ft_printf("MOOVE UP || DOWN\n\n"); //
		gr->mv.new_posx = gr->mv.log & MV_UP ? gr->rting.posx + gr->rting.dirx
							* SPEED_MV : gr->rting.posx - gr->rting.dirx
							*SPEED_MV;
		gr->mv.new_posy = gr->mv.log & MV_UP ? gr->rting.posy + gr->rting.diry
							* SPEED_MV : gr->rting.posy - gr->rting.diry
							*SPEED_MV;
		if (gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT)
		{
			//ft_printf("COMBINAISON UP/DOWN || LEFT/RIGHT\n\n"); //
			gr->mv.comb_posx = gr->mv.new_posx;
			gr->mv.comb_posy = gr->mv.new_posy;
		}
	}
	if (gr->mv.log & MV_UP && gr->mv.log & MV_DOWN)
	{
		//ft_printf("MOOVE UP && DOWN\n\n"); //
		gr->mv.new_posx = gr->rting.posx;
		gr->mv.new_posy = gr->rting.posy;
	}
}

static void	moove_left_right(t_graph *gr)
{
	if (gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT)
	{
		if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
		{
			//ft_printf("COMBINAISON LEFT/RIGHT || UP/DOWN\n\n"); //
			gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->mv.comb_posx
								- gr->rting.diry * SPEED_MV : gr->mv.comb_posx
								+ gr->rting.diry * SPEED_MV;
			gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->mv.comb_posy
								+ gr->rting.dirx * SPEED_MV : gr->mv.comb_posy
								- gr->rting.dirx * SPEED_MV;
		}
		else
		{
			//ft_printf("MOOVE LEFT || RIGHT\n\n"); //
			gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->rting.posx
								- gr->rting.diry * SPEED_MV : gr->rting.posx
								+ gr->rting.diry * SPEED_MV;
			gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->rting.posy
								+ gr->rting.dirx * SPEED_MV : gr->rting.posy
								- gr->rting.dirx * SPEED_MV;
		}
	}
	if (gr->mv.log & MV_LEFT && gr->mv.log & MV_RIGHT)
	{
		//ft_printf("MOOVE LEFT && RIGHT\n\n"); //
		gr->mv.new_posx = gr->rting.posx;
		gr->mv.new_posy = gr->rting.posy;
	}
}

void	init_moove_look(t_graph *gr, t_map *map)
{
	init_graph(gr, map);
	process_window(gr);	
}

int	moove(t_graph *gr)
{
	t_map	*map;
	double	tmp_dirx;
	double	tmp_planecamx;
	
	if (gr->update == FALSE)
		return (SUCCESS);
	if (gr->mv.log & LOOK && gr->mv.log & MOOVE)
		gr->update = TRUE;
	else
		gr->update = FALSE;
	tmp_dirx = gr->rting.dirx;
	tmp_planecamx = gr->rting.planecamx;
	map = get_map(NULL);
	if (gr->mv.log & LK_RIGHT || gr->mv.log & LK_LEFT)
		gr->mv.log & LK_RIGHT ? look_right(gr, tmp_dirx, tmp_planecamx)
									: look_left(gr, tmp_dirx, tmp_planecamx);	
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
		moove_up_down(gr);
	if (gr->mv.log & MV_RIGHT || gr->mv.log & MV_LEFT)
		moove_left_right(gr);
	if (is_wall(gr, map) == FALSE)
	{
		gr->rting.posx = gr->mv.new_posx;
		gr->rting.posy = gr->mv.new_posy;
		init_moove_look(gr, map);
	}
	else if (gr->mv.log & CAM)
		init_moove_look(gr, map);
	gr->mv.log &= ~CAM;
	return (SUCCESS);
}
