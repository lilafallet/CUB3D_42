/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:30:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/08 16:18:38 by lfallet          ###   ########.fr       */
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
			process_swap(gr, i);
			swap_sprite(gr);
		}
		i++;
	}
}

static void	init_draw_sprite(t_graph *gr, size_t i, t_map *map)
{	
	gr->sp.x = gr->sp.pos[i].x - gr->rting.posx;
	gr->sp.y = gr->sp.pos[i].y - gr->rting.posy;
	//position en x et en y par rapport au personnage
	//printf("x = %lf\n", gr->sp.x); //
	//printf("y = %lf\n", gr->sp.y); //
	gr->sp.det = 1.0 / (gr->rting.planecamx * gr->rting.diry - gr->rting.dirx
						* gr->rting.planecamy);
	//printf("det = %lf\n", gr->sp.det); //
	gr->sp.realx = gr->sp.det * (gr->rting.diry * gr->sp.x - gr->rting.dirx
						* gr->sp.y);
	//printf("realx = %lf\n", gr->sp.realx); //
	gr->sp.realy = gr->sp.det * (-gr->rting.planecamy * gr->sp.x
						+ gr->rting.planecamx * gr->sp.y);
	//printf("realy = %lf\n", gr->sp.realy); //
	gr->sp.screen = ((map->recup.resolution[AXE_X] / 2)
						* (1 + gr->sp.realx / gr->sp.realy));
	//printf("screen = %d\n", gr->sp.screen); //
	gr->sp.height = abs((int)(map->recup.resolution[AXE_Y] / gr->sp.realy));
	//printf("height = %d\n", gr->sp.height); //
	gr->sp.starty = -gr->sp.height / 2 + map->recup.resolution[AXE_Y] / 2;
	if (gr->sp.starty < 0)
		gr->sp.starty = 0;
	//printf("starty = %d\n", gr->sp.starty); //
	gr->sp.endy = gr->sp.height / 2 + map->recup.resolution[AXE_Y] / 2;
	if (gr->sp.endy >= map->recup.resolution[AXE_Y])
		gr->sp.endy	= map->recup.resolution[AXE_Y] - 1;
	//printf("endy = %d\n", gr->sp.endy); //
	gr->sp.width = abs((int)(map->recup.resolution[AXE_Y] / gr->sp.realy));
	//printf("width = %d\n", gr->sp.width); //
	gr->sp.startx = -gr->sp.width / 2 + gr->sp.screen;
	if (gr->sp.startx < 0)
		gr->sp.startx = 0;
	//printf("startx = %d\n", gr->sp.startx); //
	gr->sp.endx = gr->sp.width / 2 + gr->sp.screen;
	if (gr->sp.endx >= map->recup.resolution[AXE_X])
			gr->sp.endx = map->recup.resolution[AXE_X] - 1;	
	//printf("endx = %d\n", gr->sp.endx); //
}

static void	draw_sprite(t_graph *gr, int startx, size_t	nb_sprite, t_map *map)
{
	int	tmp_starty;
	int	mult;

	gr->sp.textx = (int)(PIXEL * (startx - (-gr->sp.width / 2
						+ gr->sp.screen))
						* gr->text.size[S][WIDTH]
						/ gr->sp.width / PIXEL);
	if (gr->sp.realy > 0 && startx > 0 && startx < map->recup.resolution[AXE_X]
			&& gr->sp.realy  < gr->sp.raybuff[startx])
	{
		tmp_starty = gr->sp.starty;
		gr->sp.textw = gr->text.size[S][WIDTH];
		while (tmp_starty < gr->sp.endy)
		{
			mult = tmp_starty * PIXEL - map->recup.resolution[AXE_Y]
					* PIXEL_DIV2 + gr->sp.height * PIXEL_DIV2;
			gr->sp.texty = ((mult * gr->text.size[S][HEIGHT] / gr->sp.height)
								/ PIXEL);
			gr->sp.color = ((int *)gr->text.data[S])[gr->sp.textw * gr->sp.texty
								+ gr->sp.textx];
			if ((gr->sp.color & 0x00FFFFFF) != 0)
			{
				gr->win.data[tmp_starty * map->recup.resolution[AXE_X] + startx]
							= gr->sp.color;
			}
			tmp_starty++;	
		}
	}	
	/*tmp_starty = gr->sp.starty;
	gr->sp.color = (int *)malloc(sizeof(int) * gr->sp.nb_sprite);
	//A PROTEGER 
	while (gr->sp.starty < gr->sp.endy)
	{
		//dessiner chaque pixel en y
		mult = (tmp_starty * PIXEL - map->recup.resolution[AXE_Y]
					* PIXEL_DIV2 + gr->sp.height * PIXEL_DIV2);
		gr->sp.texty = (mult * gr->text.size[S][HEIGHT] / gr->sp.height)
							/ PIXEL;
		//POURQUOI I ET MOI CA ?????
		if (gr->sp.texty > 0)
		{
			if (gr->text.data[S][gr->sp.textx + gr->sp.texty
					* gr->text.size[S][WIDTH]] != 0)
				gr->sp.color[nb_sprite] = gr->text.data[S][gr->sp.textx
					+ gr->sp.texty * gr->text.size[S][WIDTH]];
			else
				gr->sp.color[nb_sprite] = 0x00FFFFFF;
		}
		if (gr->sp.color[nb_sprite] != 0x00FFFFFF
				&& gr->sp.realy < gr->rting.perpwalldist)
		{
			if (startx >= 0 && startx < map->recup.resolution[AXE_X]
					&& tmp_starty >= 0
					&& tmp_starty < map->recup.resolution[AXE_Y])
				gr->win.data[startx + tmp_starty * (gr->win.size_line / 4)]
					= gr->sp.color[nb_sprite];	
		}
		gr->sp.starty++;
	}*/
}

void		hub_sprite(t_map *map, t_graph *gr)
{
	size_t	i;
	int		tmp_startx;

	i = 0;
	init_spdist(gr);
	swap_sprite(gr);
	/*while (i < gr->sp.nb_sprite) //
	{
		printf("dist[%zu] = %lf\n", i, gr->sp.dist[i]); //
		printf("pos[%zu].x = %lf , pos[%zu].y = %lf\n", i,
					gr->sp.pos[i].x, i, gr->sp.pos[i].y); //
		i++; //
	}*/
	while (i < gr->sp.nb_sprite)
	{
		init_draw_sprite(gr, i, map);
		tmp_startx = gr->sp.startx;
		//ft_printf("tmp_startx = %d\n", tmp_startx); //
		while (tmp_startx < gr->sp.endx)
		{
			//tant que plus petit que la fin du dessin en X et la resol X
			draw_sprite(gr, tmp_startx, i, map);
			//ft_printf("textx = %d\n", gr->sp.textx); //	
			//if (gr->sp.realy > 0)*/
			tmp_startx++;
		}	
		i++;
	}
}
