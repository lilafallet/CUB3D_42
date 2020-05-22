/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:43:07 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/22 16:46:12 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_moove(t_graph *gr)
{
	if (gr->mv.log & MV_UP || gr->mv.log & MV_RIGHT)
		gr->mv.mv_dir = DIR_POS;
	else if (gr->mv.log & MV_DOWN || gr->mv.log & MV_LEFT)
		gr->mv.mv_dir = DIR_NEG;
	if (gr->mv.log & LK_LEFT)
		gr->mv.lk_dir = DIR_NEG;
	else if (gr->mv.log & LK_RIGHT)
		gr->mv.lk_dir = DIR_POS;
}

static void	end_moove(t_graph *gr)
{
	if (gr->mv.log & MV_UP)
		gr->mv.mv_dir = 0;
	else if (gr->mv.log & MV_DOWN)
		gr->mv.mv_dir = 0;
	else if (gr->mv.log & MV_LEFT)
		gr->mv.mv_dir = 0;
	else if (gr->mv.log & MV_RIGHT)
		gr->mv.mv_dir = 0;
	else if (gr->mv.log & LK_LEFT)
		gr->mv.lk_dir = 0;
	else if (gr->mv.log & LK_RIGHT)
		gr->mv.lk_dir = 0;
}

int	keyrelease(int key, t_graph *gr)
{
	end_moove(gr);
	if (gr->mv.log & MV_UP)
		gr->mv.log &= ~MV_UP;
	else if (gr->mv.log & MV_DOWN)
		gr->mv.log &= ~MV_DOWN;
	else if (gr->mv.log & MV_LEFT)
		gr->mv.log &= ~MV_LEFT;
	else if (gr->mv.log & MV_RIGHT)
		gr->mv.log &= ~MV_RIGHT;
	else if (gr->mv.log & LK_LEFT)
		gr->mv.log &= ~LK_LEFT;
	else if (gr->mv.log & LK_RIGHT)
		gr->mv.log &= ~LK_RIGHT;
	return (TRUE);
}

int	keypress(int key, t_graph *gr)
{
	if (key == KMV_UP)
		gr->mv.log |= MV_UP;
	else if (key == KMV_DOWN)
		gr->mv.log |= MV_DOWN;
	else if (key == KMV_LEFT)
		gr->mv.log |= MV_LEFT;
	else if (key == KMV_RIGHT)
		gr->mv.log |= MV_RIGHT;
	else if (key == KLK_LEFT)
		gr->mv.log |= LK_LEFT;
	else if (key == KLK_RIGHT)
		gr->mv.log |= LK_RIGHT;
	init_moove(gr);
	return (TRUE);
}
