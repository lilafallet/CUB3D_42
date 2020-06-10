/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:30:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/10 09:32:20 by lfallet          ###   ########.fr       */
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
			//du plus grand au plus petit
			process_swap(gr, i);
			swap_sprite(gr);
		}
		i++;
	}
}

static void	calcdraw_sprite(t_graph *gr, size_t i, t_map *map)
{
	gr->sp.height = abs((int)(map->recup.resolution[AXE_Y] / gr->sp.playposy));
	/*permet d'avoir la hauteur du sprite selon la hauteur de l'ecran et surtout
	la position du player par rapport au sprite pour avoir de la perspective*/
	//printf("height = %d\n\n", gr->sp.height); //
	gr->sp.starty = -gr->sp.height / 2 + map->recup.resolution[AXE_Y] / 2;
	if (gr->sp.starty < 0)
		gr->sp.starty = 0;
	//pixel sur y a colorise = start
	//printf("starty = %d\n", gr->sp.starty); //
	gr->sp.endy = gr->sp.height / 2 + map->recup.resolution[AXE_Y] / 2;
	if (gr->sp.endy >= map->recup.resolution[AXE_Y])
		gr->sp.endy	= map->recup.resolution[AXE_Y] - 1;
	/*pixel sur y a colorise = end
	-> colorise de haut en bas*/
	//printf("endy = %d\n\n", gr->sp.endy); //
	gr->sp.width = abs((int)(map->recup.resolution[AXE_Y] / gr->sp.playposy));
	/*permet de savoir combien de pixel du point le plus a gauche d'au plus a
	droite il y a*/
	//printf("width = %d\n", gr->sp.width); //
	gr->sp.startx = -gr->sp.width / 2 + gr->sp.screen_where;
	if (gr->sp.startx < 0)
		gr->sp.startx = 0;
	//pixel sur x a colorise = start
	//printf("startx = %d\n", gr->sp.startx); //
	gr->sp.endx = gr->sp.width / 2 + gr->sp.screen_where;
	if (gr->sp.endx >= map->recup.resolution[AXE_X])
			gr->sp.endx = map->recup.resolution[AXE_X] - 1;	
	/*pixel sur x a colorise = end
	-> colorise de gauche a droite*/
	//printf("endx = %d\n", gr->sp.endx); //
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

static void	draw_sprite(t_graph *gr, int startx, size_t	nb_sprite, t_map *map)
{
	int	tmp_starty;
	int	dim;

	gr->sp.textx = (int)(PIXEL * (startx - (-gr->sp.width / 2
						+ gr->sp.screen_where))
						* gr->text.size[S][WIDTH]
						/ gr->sp.width / PIXEL);
	/*permet de savoir combien sur x on voit de la texture*/
	//ft_printf("textx = %d\n", gr->sp.textx); //
	if (gr->sp.playposy > 0 && startx > 0 && startx < map->recup.resolution[AXE_X]
			&& gr->sp.playposy < gr->sp.raybuff[startx])
	{
		//verifie si on est bien dans la map 
		tmp_starty = gr->sp.starty;
		gr->sp.textw = gr->text.size[S][WIDTH];
		while (tmp_starty < gr->sp.endy)
		{
			dim = tmp_starty * PIXEL - map->recup.resolution[AXE_Y]
					* PIXEL_DIV2 + gr->sp.height * PIXEL_DIV2;
			/*permet d'avoir la dimension de la texture
			-> 1er mult = largeur en pixel du sprite
			-> 2eme mult = quel pixel position moitie ecran
			-> 3eme mult = hauteur en pixel du sprite
			== largeur - position moitie ecran + hauteur*/
			gr->sp.texty = ((dim * gr->text.size[S][HEIGHT] / gr->sp.height)
								/ PIXEL);
			/*permet de de savoir sur quel pixel sur Y on se situe
			(dimension du pixel * taille de l'image du pixel / hauteur du sprite
			reel / 256 (nombre de pixel))*/
			gr->sp.color = ((int *)gr->text.data[S])[gr->sp.textw * gr->sp.texty
								+ gr->sp.textx];
			if ((gr->sp.color & 0xFFFFFF) != 0)
			{
				gr->win.data[tmp_starty * map->recup.resolution[AXE_X] + startx]
							= gr->sp.color;
			}
			tmp_starty++;	
		}
	}	
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
		calcdraw_sprite(gr, i, map);
		tmp_startx = gr->sp.startx;
		//ft_printf("tmp_startx = %d\n", tmp_startx); //
		while (tmp_startx < gr->sp.endx)
		{
			//tant que plus petit que la fin du dessin en X et la resol X
			draw_sprite(gr, tmp_startx, i, map);
			//ft_printf("textx = %d\n", gr->sp.textx); //	
			tmp_startx++;
		}	
		i++;
	}
}
