/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:23:14 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/22 15:54:05 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	colorisation_sprite(t_graph *gr, int starty, int startx, t_map *map)
{
	gr->sp.color = ((int *)gr->text.data[S])[gr->sp.textw * gr->sp.texty
						+ gr->sp.textx];
	/*permet de savoir a quel coordonnes de data on se situe et recupere
	la couleur de la coordonnee*/
	if ((gr->sp.color & 0xFFFFFF) != 0)
	{
		gr->win.data[starty * map->recup.resolution[AXE_X] + startx]
						= gr->sp.color;
	}
	//permet de coloriser le pixel en x/y de la fenetre
}

void	draw_sprite(t_graph *gr, int startx, t_map *map)
{
	int	tmp_starty;
	int	dim;

	gr->sp.textx = (int)(PIXEL * (startx - (-gr->sp.width / 2
						+ gr->sp.screen_where))
						* gr->text.size[S][WIDTH]
						/ gr->sp.width / PIXEL);
	/*permet de savoir combien sur x on voit de la texture, quel x on est*/
	//ft_printf("textx = %d\n", gr->sp.textx); //
	if (gr->sp.playposy > 0 && startx >= 0 && startx < map->recup.resolution[AXE_X]
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
			colorisation_sprite(gr, tmp_starty, startx, map);
			tmp_starty++;	
		}
	}	
}

void	calcdraw_sprite(t_graph *gr, t_map *map)
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
			gr->sp.endx = map->recup.resolution[AXE_X];	
	/*pixel sur x a colorise = end
	-> colorise de gauche a droite*/
	//printf("endx = %d\n", gr->sp.endx); //
}
