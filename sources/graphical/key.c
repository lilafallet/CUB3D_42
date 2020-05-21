/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:43:07 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/21 09:53:29 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keyrelease(int key, t_graph *gr)
{
	if (gr->key.log & MV_UP)
		gr->key.log &= ~MV_UP;
	else if (gr->key.log & MV_DOWN)
		gr->key.log &= ~MV_DOWN;
	else if (gr->key.log & MV_LEFT)
		gr->key.log &= ~MV_LEFT;
	else if (gr->key.log & MV_RIGHT)
		gr->key.log &= ~MV_RIGHT;
	else if (gr->key.log & LK_LEFT)
		gr->key.log &= ~LK_LEFT;
	else if (gr->key.log & LK_RIGHT)
		gr->key.log &= ~LK_RIGHT;
	return (SUCCESS);
}

int	keypress(int key, t_graph *gr)
{
	if (key == KMV_UP)
		gr->key.log |= MV_UP;
	else if (key == KMV_DOWN)
		gr->key.log |= MV_DOWN;
	else if (key == KMV_LEFT)
		gr->key.log |= MV_LEFT;
	else if (key == KMV_RIGHT)
		gr->key.log |= MV_RIGHT;
	else if (key == KLK_LEFT)
		gr->key.log |= LK_LEFT;
	else if (key == KLK_RIGHT)
		gr->key.log |= LK_RIGHT;
	return (SUCCESS);
}
