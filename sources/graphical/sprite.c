/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:30:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/06 17:00:52 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_spdist(t_graph *gr)
{
	size_t	i;
	double	distx;
	double	disty;

	i = 0;
	gr->sp.dist = (double *)malloc(sizeof(double) * gr->sp.nb_sprite);
	//A PROTEGER
	while (i < gr->sp.nb_sprite)
	{
		distx = ft_lfpow(gr->rting.posx - gr->sp.pos[i].x, POW_2);
		disty = ft_lfpow(gr->rting.posy - gr->sp.pos[i].y, POW_2);
		/*pour trouver la distance entre la position actuelle et la position
		du sprite il faut faire la position - la position du sprite
		pow 2 car on est sur 2 axes (x et y)*/
		gr->sp.dist[i] = distx + disty;
		printf("dist[%zu] = %lf\n", i, gr->sp.dist[i]); //
		i++;
	}
	printf("\n"); //
}

static void	process_swap(t_graph *gr, size_t i)
{
	double	tmp_dist;
	double	tmp_x;
	double	tmp_y;

	tmp_dist = 0; //
	tmp_x = 0; //
	tmp_y = 0; //
	//printf("tmp_dist = %lf\n", tmp_dist); //
	//printf("tmp_x = %lf\n", tmp_x); //
	//printf("tmp_y = %lf\n", tmp_x); //
	//printf("dist[%zu] = %lf\n", i, gr->sp.dist[i]); //
	//printf("pos[%zu].x = %lf\n", i, gr->sp.pos[i].x); //
	//printf("pos[%zu].y = %lf\n", i, gr->sp.pos[i].y); //
	//printf("dist[%zu (+1)] = %lf\n", i + 1, gr->sp.dist[i + 1]); //
	//printf("pos[%zu (+1)].x = %lf\n", i + 1, gr->sp.pos[i + 1].x); //
	//printf("pos[%zu (+1)].y = %lf\n", i + 1, gr->sp.pos[i + 1].y); //
	tmp_dist = gr->sp.dist[i];
	tmp_x = gr->sp.pos[i].x;
	tmp_y = gr->sp.pos[i].y;
	gr->sp.dist[i] = gr->sp.dist[i + 1];
	gr->sp.pos[i].x = gr->sp.pos[i + 1].x;
	gr->sp.pos[i].y = gr->sp.pos[i + 1].y;
	gr->sp.dist[i + 1] = tmp_dist;
	gr->sp.pos[i + 1].x = tmp_x;
	gr->sp.pos[i + 1].y = tmp_y;
	//printf("tmp_dist aft = %lf\n", tmp_dist); //
	//printf("tmp_x aft = %lf\n", tmp_x); //
	//printf("tmp_y aft = %lf\n", tmp_x); //
	//printf("dist[%zu] aft = %lf\n", i, gr->sp.dist[i]); //
	//printf("pos[%zu].x aft = %lf\n", i, gr->sp.pos[i].x); //
	//printf("pos[%zu].y aft = %lf\n", i, gr->sp.pos[i].y); //
	//printf("dist[%zu (+1)] aft = %lf\n", i + 1, gr->sp.dist[i + 1]); //
	//printf("pos[%zu (+1)].x aft = %lf\n", i + 1, gr->sp.pos[i + 1].x); //
	//printf("pos[%zu (+1)].y aft = %lf\n\n", i + 1, gr->sp.pos[i + 1].y); //
	tmp_dist = gr->sp.dist[i];
}

static void	swap_sprite(t_graph *gr)
{
	size_t	i;

	i = 0;
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

void		hub_sprite(t_map *map, t_graph *gr)
{
	//size_t	i; //

	//i = 0; //
	init_spdist(gr);
	swap_sprite(gr);
	/*while (i < gr->sp.nb_sprite) //
	{
		printf("dist[%zu] = %lf\n", i, gr->sp.dist[i]); //
		printf("pos[%zu].x = %lf , pos[%zu].y = %lf\n", i,
					gr->sp.pos[i].x, i, gr->sp.pos[i].y); //
		i++; //
	}*/
}
