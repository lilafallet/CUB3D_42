/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 17:43:07 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/03 15:19:31 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keyrelease(int key, t_graph *gr)
{
	if (gr->mv.log & MV_UP && key == KMV_UP)
	{
		//ft_printf("DESACTIVE MV UP\n"); //
		gr->mv.log &= ~MV_UP;
	}
	if (gr->mv.log & MV_DOWN && key == KMV_DOWN)
	{
		//ft_printf("DESACTIVE MV DOWN\n"); //
		gr->mv.log &= ~MV_DOWN;
	}
	if (gr->mv.log & MV_LEFT && key == KMV_LEFT)
	{
		//ft_printf("DESACTIVE MV LEFT\n"); //
		gr->mv.log &= ~MV_LEFT;
	}
	if (gr->mv.log & MV_RIGHT && key == KMV_RIGHT)
	{
		//ft_printf("DESACTIVE MV RIGHT\n"); //
		gr->mv.log &= ~MV_RIGHT;
	}
	if (gr->mv.log & LK_LEFT && key == KLK_LEFT)
	{
		//ft_printf("DESACTIVE LK LEFT\n"); //
		gr->mv.log &= ~LK_LEFT;
	}
	if (gr->mv.log & LK_RIGHT && key == KLK_RIGHT)
	{
		//ft_printf("DESACTIVE LK RIGHT\n"); //
		gr->mv.log &= ~LK_RIGHT;
	}
	return (TRUE);
}

int	keypress(int key, t_graph *gr)
{
	int		mask;

	mask = gr->mv.log;
	if (key == KMV_UP && (gr->mv.log & MV_UP) == FALSE)
	{
		//ft_printf("ACTIVE MV UP\n"); //
		gr->mv.log |= MV_UP;
	}
	if (key == KMV_DOWN && (gr->mv.log & MV_DOWN) == FALSE)
		gr->mv.log |= MV_DOWN;
	if (key == KMV_LEFT && (gr->mv.log & MV_LEFT) == FALSE)
	{
		//ft_printf("ACTIVE MV LEFT\n"); //
		gr->mv.log |= MV_LEFT;
	}
	if (key == KMV_RIGHT && (gr->mv.log & MV_RIGHT) == FALSE)
	{
		//ft_printf("ACTIVE MV RIGHT\n"); //
		gr->mv.log |= MV_RIGHT;
	}
	if (key == KLK_LEFT && (gr->mv.log & LK_LEFT) == FALSE)
	{
		//ft_printf("ACTIVE LK LEFT\n"); //
		gr->mv.log |= LK_LEFT;
	}
	if (key == KLK_RIGHT && (gr->mv.log & LK_RIGHT) == FALSE)
	{
		//ft_printf("ACTIVE LK RIGHT\n"); //
		gr->mv.log |= LK_RIGHT;
	}
	if (gr->mv.log & MV_UP || gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT
			|| gr->mv.log & MV_DOWN)
	{
		//ft_printf("ACTIVE MOOVE\n"); //
		gr->mv.log |= MOOVE;
	}
	if (gr->mv.log & LK_LEFT || gr->mv.log & LK_RIGHT)
	{
		//ft_printf("ACTIVE LOOK\n"); //
		gr->mv.log |= LOOK;
	}
	if (mask != gr->mv.log)
		gr->update = TRUE;
	return (TRUE);
}
