/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:30:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/22 18:27:31 by lfallet          ###   ########.fr       */
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
	if (gr->sp.dist == NULL)
	{
		//A PROTEGER
		exitred(gr);
	}
	while (i < gr->sp.nb_sprite)
	{
		distx = ft_lfpow(gr->rting.posx - gr->sp.pos[i].x, POW_2);
		disty = ft_lfpow(gr->rting.posy - gr->sp.pos[i].y, POW_2);
		/*pour trouver la distance entre la position actuelle et la position
		du sprite il faut faire la position - la position du sprite
		pow 2 car on est sur 2 axes (x et y)*/
		gr->sp.dist[i] = distx + disty;
		//printf("dist[%zu] = %lf\n", i, gr->sp.dist[i]); //
		i++;
	}
	//printf("\n"); //
}

static void	process_swap(t_graph *gr, size_t i)
{
	double	tmp_dist;
	double	tmp_x;
	double	tmp_y;

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
}

static void	swap_sprite(t_graph *gr)
{
	size_t	i;

	i = 0;
	while (i < gr->sp.nb_sprite - 1)
	{
		if (gr->sp.dist[i] < gr->sp.dist[i + 1])
		{
			//du plus grand au plus petit
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
	//position en x et en y par rapport au personnage
	//printf("x = %lf\n", gr->sp.x); //
	//printf("y = %lf\n", gr->sp.y); //
	gr->sp.rot = 1.0 / (gr->rting.planecamx * gr->rting.diry - gr->rting.dirx
						* gr->rting.planecamy);
	//permet de faire la rotation/inverstion en fonction du deplacement
	//printf("rot = %lf\n\n", gr->sp.rot); //
	gr->sp.playposx = gr->sp.rot * (gr->rting.diry * gr->sp.x - gr->rting.dirx
						* gr->sp.y);
	/*position du jour sur x par rapport au sprite
	->negt = a gauche du sprite donc joueur a droite
	->post = a droite du sprite donc joueur a gauche*/
	//printf("playposx = %lf\n\n", gr->sp.playposx); //
	gr->sp.playposy = gr->sp.rot * (-gr->rting.planecamy * gr->sp.x
						+ gr->rting.planecamx * gr->sp.y);
	/*position du jour sur y par rapport au sprite
	->negt = en haut du sprite
	->post = en bas du sprite*/
	//printf("playposy = %lf\n\n", gr->sp.playposy); //
	gr->sp.screen_where = ((map->recup.resolution[AXE_X] / 2)
						* (1 + gr->sp.playposx / gr->sp.playposy));
	/*permet de savoir vers quel direction on regarde, valeurs changent en
	fonction de quel mur on regarde/quel combinaison de mur on regarde
	-> des qu'on regarde le NORD/SUD valeur positive
	-> ouest = premiere moitie negative / deuxieme positive
	-> est = premiere moitie positive / deuxieme negative
	= plus on va vers l'ouest, plus la valeur augmente
	= plus on va vers l'est, plus la valeur diminue*/
	//printf("screen_where = %d\n\n", gr->sp.screen_where); //
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
		//ft_printf("tmp_startx = %d\n", tmp_startx); //
		while (tmp_startx < gr->sp.endx)
		{
			//tant que plus petit que la fin du dessin en X et la resol X
			draw_sprite(gr, tmp_startx, map);
			//ft_printf("textx = %d\n", gr->sp.textx); //	
			tmp_startx++;
		}	
		i++;
	}
	free(gr->sp.dist);
}
