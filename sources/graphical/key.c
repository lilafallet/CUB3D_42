/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:43:07 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/30 10:55:26 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int		mask;

	mask = gr->mv.log;
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
	if (gr->mv.log & MV_UP || gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT
			|| gr->mv.log & MV_DOWN)
		gr->mv.log |= MOOVE;
	if (gr->mv.log & LK_LEFT || gr->mv.log & LK_RIGHT)
		gr->mv.log |= LOOK;
	if (mask != gr->mv.log)
		gr->update = TRUE;
	return (TRUE);
}
