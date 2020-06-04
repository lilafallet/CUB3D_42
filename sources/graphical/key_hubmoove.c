/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hubmoove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:05:25 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/04 12:11:38 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_moove_look(t_graph *gr, t_map *map)
{
	//static int	i = 1;

	//ft_printf("RAYCASTING %d\n", i); //
	//i++;
	init_graph(gr, map);
	process_window(gr);	
}

static void	hub_moove_look(t_graph *gr)
{
	double	tmp_dirx;
	double	tmp_planecamx;
	
	tmp_dirx = gr->rting.dirx;
	tmp_planecamx = gr->rting.planecamx;
	if (gr->mv.log & LK_RIGHT || gr->mv.log & LK_LEFT)
		gr->mv.log & LK_RIGHT ? look_right(gr, tmp_dirx, tmp_planecamx)
									: look_left(gr, tmp_dirx, tmp_planecamx);	
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
		moove_up_down(gr);
	if (gr->mv.log & MV_RIGHT || gr->mv.log & MV_LEFT)
		moove_left_right(gr);
}

int	moove(t_graph *gr)
{
	t_map	*map;
	static int	i = 1; //
	gr->update = 0;
	
	if (update(gr) == TRUE)
		gr->update = 1;
	if (gr->update == 1)
	{
		//ft_printf("UPDATE %d\n", i); //
		i++; //
		map = get_map(NULL);
		hub_moove_look(gr);
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
	//ft_printf("NO UPDATE %d\n", i); //
	return (FALSE);
}

int	keyrelease(int key, t_graph *gr)
{
	if (gr->mv.log & MV_UP && key == KMV_UP)
	{
		//ft_printf("REL UP\n"); //
		gr->mv.log &= ~MV_UP;
	}
	if (gr->mv.log & MV_DOWN && key == KMV_DOWN)
	{
		//ft_printf("REL DOWN\n"); //
		gr->mv.log &= ~MV_DOWN;
	}
	if (gr->mv.log & MV_LEFT && key == KMV_LEFT)
	{
		//ft_printf("REL LEFT\n"); //
		gr->mv.log &= ~MV_LEFT;
	}
	if (gr->mv.log & MV_RIGHT && key == KMV_RIGHT)
	{
		//ft_printf("REL RIGHT\n"); //
		gr->mv.log &= ~MV_RIGHT;
	}
	if (gr->mv.log & LK_LEFT && key == KLK_LEFT)
	{
		//ft_printf("REL LK LEFT\n"); //
		gr->mv.log &= ~LK_LEFT;
	}
	if (gr->mv.log & LK_RIGHT && key == KLK_RIGHT)
	{
		//ft_printf("REL LK RIGHT\n"); //
		gr->mv.log &= ~LK_RIGHT;
	}
	return (TRUE);
}

int	keypress(int key, t_graph *gr)
{
	if (key == KMV_UP && (gr->mv.log & MV_UP) == FALSE)
	{
		//ft_printf("UP\n"); //
		gr->mv.log |= MV_UP;
	}
	if (key == KMV_DOWN && (gr->mv.log & MV_DOWN) == FALSE)
	{
		//ft_printf("DOWN\n"); //
		gr->mv.log |= MV_DOWN;
	}
	if (key == KMV_LEFT && (gr->mv.log & MV_LEFT) == FALSE)
	{
		//ft_printf("LEFT\n"); //
		gr->mv.log |= MV_LEFT;
	}
	if (key == KMV_RIGHT && (gr->mv.log & MV_RIGHT) == FALSE)
	{
		//ft_printf("RIGHT\n"); //
		gr->mv.log |= MV_RIGHT;
	}
	if (key == KLK_LEFT && (gr->mv.log & LK_LEFT) == FALSE)
	{
		//ft_printf("LK LEFT\n"); //
		gr->mv.log |= LK_LEFT;
	}
	if (key == KLK_RIGHT && (gr->mv.log & LK_RIGHT) == FALSE)
	{
		//ft_printf("LK RIGHT\n"); //
		gr->mv.log |= LK_RIGHT;
	}
	return (TRUE);
}
