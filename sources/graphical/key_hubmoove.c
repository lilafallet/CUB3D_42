/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hubmoove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:05:25 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/22 17:33:31 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_moove_look(t_graph *gr, t_map *map)
{
		init_graph(gr, map);
		process_window(gr);
	//	if (gr->mv.new_posx == gr->mv.old_posx + SPEED_MV
	//		|| gr->mv.new_posx == gr->mv.old_posx - SPEED_MV)
			gr->mv.old_posx = gr->mv.new_posx;
	//	if (gr->mv.new_posy == gr->mv.old_posy + SPEED_MV
	//		|| gr->mv.new_posy == gr->mv.old_posy - SPEED_MV)
			gr->mv.old_posy = gr->mv.new_posy;
}

static void	hub_moove_look(t_graph *gr)
{
	double	tmp_dirx;
	double	tmp_planecamx;
	
	tmp_dirx = gr->rting.dirx;
	tmp_planecamx = gr->rting.planecamx;
	/*permet d'avoir des variables temp afin de faire toutes les verifications
	necessaires avant de les actualiser reellement*/
	if (gr->mv.log & LK_RIGHT || gr->mv.log & LK_LEFT)
	{
		if ((gr->mv.log & LK_LEFT && ((gr->mv.log & LK_RIGHT) == FALSE))
				|| (gr->mv.log & LK_RIGHT && ((gr->mv.log & LK_LEFT) == FALSE)))
				gr->mv.log & LK_RIGHT ? look_right(gr, tmp_dirx, tmp_planecamx)
										: look_left(gr, tmp_dirx, tmp_planecamx);
	}
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
		moove_up_down(gr);
	if (gr->mv.log & MV_RIGHT || gr->mv.log & MV_LEFT)
		moove_left_right(gr);
}

int	moove(t_graph *gr)
{
	t_map	*map;
	
	if (update(gr) == TRUE)
	{
		map = get_map(NULL);
		hub_moove_look(gr);
		is_wall(gr, map); //BONUS
		gr->rting.posx = gr->mv.new_posx;
		gr->rting.posy = gr->mv.new_posy;
		init_moove_look(gr, map);
		return (SUCCESS);
	}
	return (FALSE);
}

int	keyrelease(int key, t_graph *gr)
{
	if (gr->mv.log & MV_UP && key == KMV_UP)
		gr->mv.log &= ~MV_UP;
	if (gr->mv.log & MV_DOWN && key == KMV_DOWN)
		gr->mv.log &= ~MV_DOWN;
	if (gr->mv.log & MV_LEFT && key == KMV_LEFT)
		gr->mv.log &= ~MV_LEFT;
	if (gr->mv.log & MV_RIGHT && key == KMV_RIGHT)
		gr->mv.log &= ~MV_RIGHT;
	if (gr->mv.log & LK_LEFT && key == KLK_LEFT)
		gr->mv.log &= ~LK_LEFT;
	if (gr->mv.log & LK_RIGHT && key == KLK_RIGHT)
		gr->mv.log &= ~LK_RIGHT;
	return (TRUE);
}

int	keypress(int key, t_graph *gr)
{
	if (key == KEY_ESCAPE)
		exitred(gr);
	if (key == KMV_UP && (gr->mv.log & MV_UP) == FALSE)
		gr->mv.log |= MV_UP;
	if (key == KMV_DOWN && (gr->mv.log & MV_DOWN) == FALSE)
		gr->mv.log |= MV_DOWN;
	if (key == KMV_LEFT && (gr->mv.log & MV_LEFT) == FALSE)
		gr->mv.log |= MV_LEFT;
	if (key == KMV_RIGHT && (gr->mv.log & MV_RIGHT) == FALSE)
		gr->mv.log |= MV_RIGHT;
	if (key == KLK_LEFT && (gr->mv.log & LK_LEFT) == FALSE)
		gr->mv.log |= LK_LEFT;
	if (key == KLK_RIGHT && (gr->mv.log & LK_RIGHT) == FALSE)
		gr->mv.log |= LK_RIGHT;
	return (TRUE);
}
