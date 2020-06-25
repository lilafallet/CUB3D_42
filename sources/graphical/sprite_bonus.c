/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:19:38 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:19:39 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_spdist(t_graph *gr)
{
	size_t	i;
	double	distx;
	double	disty;

	i = 0;
	gr->sp.dist = (double *)malloc(sizeof(double) * gr->sp.nb_sprite);
	if (gr->sp.dist == NULL)
	{
		printf_errors(ERROR_MALLOC_DIST, 0, NULL);
		exitred(gr, FAILURE);
	}
	while (i < gr->sp.nb_sprite)
	{
		distx = ft_lfpow(gr->rting.posx - gr->sp.pos[i].x, POW_2);
		disty = ft_lfpow(gr->rting.posy - gr->sp.pos[i].y, POW_2);
		gr->sp.dist[i] = distx + disty;
		i++;
	}
}

static void	process_swap(t_graph *gr, size_t i)
{
	double	tmp_dist;
	double	tmp_x;
	double	tmp_y;

	tmp_dist = gr->sp.dist[i];
	tmp_x = gr->sp.pos[i].x;
	tmp_y = gr->sp.pos[i].y;
	gr->sp.dist[i] = gr->sp.dist[i + 1];
	gr->sp.pos[i].x = gr->sp.pos[i + 1].x;
	gr->sp.pos[i].y = gr->sp.pos[i + 1].y;
	gr->sp.dist[i + 1] = tmp_dist;
	gr->sp.pos[i + 1].x = tmp_x;
	gr->sp.pos[i + 1].y = tmp_y;
}

static void	swap_sprite(t_graph *gr)
{
	size_t	i;

	i = 0;
	if (gr->sp.nb_sprite < 2)
		return ;
	while (i < gr->sp.nb_sprite - 1)
	{
		if (gr->sp.dist[i] < gr->sp.dist[i + 1])
		{
			process_swap(gr, i);
			swap_sprite(gr);
		}
		i++;
	}
}

static void	calcpos_sprite(t_graph *gr, size_t i, t_map *map)
{
	gr->sp.x = gr->sp.pos[i].x - gr->rting.posx;
	gr->sp.y = gr->sp.pos[i].y - gr->rting.posy;
	gr->sp.rot = 1.0 / (gr->rting.planecamx * gr->rting.diry - gr->rting.dirx
						* gr->rting.planecamy);
	gr->sp.playposx = gr->sp.rot * (gr->rting.diry * gr->sp.x - gr->rting.dirx
						* gr->sp.y);
	gr->sp.playposy = gr->sp.rot * (-gr->rting.planecamy * gr->sp.x
						+ gr->rting.planecamx * gr->sp.y);
	gr->sp.screen_where = ((map->recup.resolution[AXE_X] / 2)
						* (1 + gr->sp.playposx / gr->sp.playposy));
}

void		hub_sprite(t_map *map, t_graph *gr)
{
	size_t	i;
	int		tmp_startx;

	i = 0;
	init_spdist(gr);
	swap_sprite(gr);
	while (i < gr->sp.nb_sprite)
	{
		calcpos_sprite(gr, i, map);
		calcdraw_sprite(gr, map);
		tmp_startx = gr->sp.startx;
		while (tmp_startx < gr->sp.endx)
		{
			draw_sprite(gr, tmp_startx, map);
			tmp_startx++;
		}
		i++;
	}
	free(gr->sp.dist);
}
