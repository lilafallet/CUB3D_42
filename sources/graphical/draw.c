/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:45:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/18 15:55:00 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_map *map, t_graph *gr, int x)
{
	int		y;
	int		who;

	who = what_texture(gr);
	if (gr->rting.side == 0)
	{
			gr->text.wallhit = gr->rting.posy + gr->rting.perpwalldist
								* gr->rting.raydiry;
			//la ou le mur a ete exactement tappe sur y
	}
	else
	{
			gr->text.wallhit = gr->rting.posx + gr->rting.perpwalldist
								* gr->rting.raydirx;
			//la ou le mur a ete exactement tappe sur x
	}
	gr->text.wallhit -= floor(gr->text.wallhit); /*la fonction floor permet de
	prendre la valeur du dessous (ex floor(2.51) = 2) -> permet d'avoir une
	ligne bien droite*/
	printf("wallhit = %lf\n", gr->text.wallhit); //
	gr->text.texx = gr->text.wallhit * (double)gr->text.size[who][WIDTH];
	/*permet d'avoir la position du pixel sur x = la ou a ete tappe le mur
	* la largeur de l'image EUUUUH BIZARRE NON*/
	printf("texx = %d\n", gr->text.texx); //
	y = gr->draw.start;
	while (y < gr->draw.end)
	{
		gr->text.texy = (y - map->recup.resolution[AXE_Y] / 2
							+ gr->draw.height_line / 2)
							* gr->text.size[who][HEIGHT] / gr->draw.height_line;
		/*permet d'avoir la position du pixel sur y = debut du pixel
		- la resolution sur y (div par 2) + la hauteur du mur (div par 2)
		* la hauteur de l'image / par la hauteur du mur EUUUH BIZARRE NON*/ 
		printf("texy = %d\n", gr->text.texy); //
		gr->win.data[x + y * (gr->win.size_line / 4)] =
						gr->text.data[who][gr->text.texx + gr->text.texy
						* gr->text.size[who][WIDTH]];
		/*permet de mettre le pixel de l'image dans la data de la fenetre au
		pixel correspondant = position sur x de la fenetre + position sur y
		de la fenetre * (A QUOI CORRESPOND SIZELINE ??) / 4 (POURQUOI 4) = 
		le pixel de la texture x + pixel de la texture y * la largeur de la
		texture*/
		printf("data = %d\n", x + y * (gr->win.size_line / 4)); //
		printf("content = %d\n\n", gr->text.data[who][gr->text.texx
		+ gr->text.texy * gr->text.size[who][WIDTH]]); //
		y++;
	}
}

static void	draw_floor(t_map *map, t_graph *gr, int x)
{
	int	y;
	int	floor_color;

	y = map->recup.resolution[AXE_Y] - 1;
	floor_color = get_rgb(map->recup.tab_color_f[R], map->recup.tab_color_f[G],
							map->recup.tab_color_f[B]); 
	while (y >= gr->draw.end) /*colorise les pixels en montant sur y (jusqu'a
	draw start qui correspond au pixel jusqu'a ou on peut allez*/
	{
		gr->win.data[y * map->recup.resolution[AXE_X] + x] = floor_color;
		//pixel a coloriser sur win
		y--;
	}
}

static void	draw_sky(t_map *map, t_graph *gr, int x)
{
	int	y;
	int	sky_color;
	
	y = 0;
	sky_color = get_rgb(map->recup.tab_color_c[R], map->recup.tab_color_c[G],
							map->recup.tab_color_c[B]); 
	while (y < gr->draw.start) /*colorise les pixels en descendant sur y
	(jusqu'a draw start qui correspond au pixel jusqu'a ou on peut aller*/
	{
		gr->win.data[y * map->recup.resolution[AXE_X] + x] = sky_color;
		//pixel a coloriser sur win
		y++;
	}
}

void	shadow_wall(t_graph *gr) //DETERMINER COMMENT JE VAIS DEVOIR L'UTILSER
{
	gr->color.south = 0x0066CC; //BLUE
	gr->color.north = 0x990000; //RED
	gr->color.east = 0xFFD700; //YELLOW
	gr->color.west = 0x009900; //GREEN
	
	if (gr->rting.side == 0 && gr->rting.raydirx > 0)
		gr->color.wall = gr->color.north; //ombre
	else if (gr->rting.side == 0 && gr->rting.raydirx < 0)
		gr->color.wall = gr->color.south;	//ombre
	else if (gr->rting.side == 1 && gr->rting.raydiry > 0)
		gr->color.wall = gr->color.east;	//ombre
	else
		gr->color.wall = gr->color.west;	//ombre
}

void	hub_draw(t_map *map, t_graph *gr, int x)
{
	draw_floor(map, gr, x);
	draw_sky(map, gr, x);
}
