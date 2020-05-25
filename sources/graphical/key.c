/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:43:07 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/25 19:22:31 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keyrelease(int key, t_graph *gr)
{
	if (gr->mv.log & MV_UP && key == KMV_UP)
	{
		ft_printf("RELEASE MV UP\n"); //
		gr->mv.log &= ~MV_UP;
	}
	else if (gr->mv.log & MV_DOWN && key == KMV_DOWN)
	{
		ft_printf("RELEASE MV DOWN\n"); //
		gr->mv.log &= ~MV_DOWN;
	}
	if (gr->mv.log & MV_LEFT && key == KMV_LEFT)
	{
		ft_printf("RELEASE MV LEFT\n"); //
		gr->mv.log &= ~MV_LEFT;
	}
	else if (gr->mv.log & MV_RIGHT && key == KMV_RIGHT)
	{
		ft_printf("RELEASE MV RIGHT\n"); //
		gr->mv.log &= ~MV_RIGHT;
	}
	if (gr->mv.log & LK_LEFT && key == KLK_LEFT)
	{
		ft_printf("RELEASE LOOK LEFT\n"); //
		gr->mv.log &= ~LK_LEFT;
	}
	else if (gr->mv.log & LK_RIGHT && key == KLK_RIGHT)
	{
		ft_printf("RELEASE LOOK RIGHT\n"); //
		gr->mv.log &= ~LK_RIGHT;
	}
	return (TRUE);
}

int	keypress(int key, t_graph *gr)
{
	if (key == KMV_UP && (gr->mv.log & MV_UP) == FALSE)
	{
		ft_printf("KEY UP\n"); //
		gr->mv.log |= MV_UP;
	}
	else if (key == KMV_DOWN && (gr->mv.log & MV_DOWN) == FALSE)
		gr->mv.log |= MV_DOWN;
	if (key == KMV_LEFT && (gr->mv.log & MV_LEFT) == FALSE)
		gr->mv.log |= MV_LEFT;
	else if (key == KMV_RIGHT && (gr->mv.log & MV_RIGHT) == FALSE)
		gr->mv.log |= MV_RIGHT;
	if (key == KLK_LEFT && (gr->mv.log & LK_LEFT) == FALSE)
	{
		ft_printf("KEY UP\n"); //
		gr->mv.log |= LK_LEFT;
	}
	else if (key == KLK_RIGHT && (gr->mv.log & LK_RIGHT) == FALSE)
		gr->mv.log |= LK_RIGHT;
	return (TRUE);
}
