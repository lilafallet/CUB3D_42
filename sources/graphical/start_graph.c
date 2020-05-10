/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/10 21:25:29 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	keys(unsigned char key, int x, int y, t_rting *rting)
{
	if (key == 'a')
	{
		rting->pangle -= 0.1
		if (rting->pangle < 0)
			rting->pangle += 2 * PI;
		rting->deltapx = cos(rting->pangle) * 5;
		rting->deltapy = sin(rting->pangle) * 5;
	}
	else if (key == 'd')
	{
		rting->pangle += 0.1;
		if (rting->pangle > 2 * PI)
			rting->pangle -= 2 * PI;
		rting->delatpx = cos(rting->pangle) * 5;
		rting->deltapy = sin(rting->pangle) * 5;
	}
	else if (key == 'w')
	{
		rting->px += rting->deltapx;
		rting->py += rting->deltapy;
	}
	else if (key == 's')
	{
		rting->px -= rting->deltapx;
		rting->py -= rting->deltapy;
	}
	else if (key == 's')
	//glutPostReDisplay();	
}

static double dist_endray_play(double ax, double ay, double bx, double by,
								double ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))); /*retourne la distance entre
	le joueur et la fin du rayon*/
}

static void draw_rays2d(t_rting *rting, t_map *map)
{
	int		ray;
	double	rayangle;
	int		dof;
	double	atan;
	double	ntan;
	double	dish;
	double	disv;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	double	distfinal; //distance finale

	ray = 0;
	rayangle = rting->pangle - DR * 30; //set l'angle a l'angle du joueur -> 30 = 30degres
	if (rayangle < 0)
		rayangle += 2 * PI;
	if (rayangle > 2 * PI)
		rayangle -= 2 * PI;
	while (ray < 60) //60 = 60degres
	{
		//check les lignes horizontales
		dof = 0;
		dish = 1000000; //tres grande valeur car on recherche la plus petite distance
		hx = rting->px; //horizontal rayx
		hy = rting->py; //horizontal rayy
		atan = -1 / tan(rayangle); //negative indverse tangeant->commencer le rayon a gauche
		if (rayangle > PI) //le rayon monte (donc descend en y et en x)
		{
			rting->rayy = (((int)rting->py>>6)<<6) - 0.0001; /*trouver le prochain point qui touchera
			les lignes horizontales (x) --> diviser la position y par 64 (shift de 6), puis le
			multiplier par 64 (shift de 6)* et lui enlever la plus petit valeurs sur 64bits (pour
			pouvoir descendre)*/
			rting->rayx = (ring->py - rting->rayy) * atan + rting->px; /*rayx est la difference entre
			la position du player sur y et le rayon de y multiplier par l'inverse de la tengante
			+ la position x du joueur*/
			rting->yo = -64; //vu qu'on monte en haut en descend sur y
			rting->xo = -rting->yo * atan; /*position yo * l'inverse de la tengeante (on descend a
			la fois en y et en x*/
		}
		if (rayangle < PI) //le de rayon descend (donc monte en y et monte en x)
		{
			rting->rayy = (((int)rting->py>>6)<<6) + 64;
			rting->rayx = (rting->py - rting->rayy) * atan + rting->px;
			rting->yo = 64; //vu qu'on descend, on monte en y
			rting->xo = -rting->yo * atan; /*position de yo qui est posotif donc multiplier par
			la negative de la tengante fait qu'on monte a la fois en x et en y*/
		}
		if (rting->rayangle == 0 || rting->rayangle == PI) /*si le rayon regarde directement a
		gauche ou a droite, c'est impossible pour le rayon de toucher une ligne horizontale (y)*/
		{
			rting->rayx = rting->px; //devient directement la position du joueur en x
			rting->rayy = rting->py; //devient directement la position du joueur en y
			dof = rting->mapx;
		}
		while (dof < rting->mapx) /*boucle qui permet de verifier jusqu'a la taille de x*/
		{
			rting->mx = (int)(rting->rayx) >> 6; /*largeur du rayon = prendre la position du
			rayon x et le diviser par 64*/
			rting->my = (int)(rting->rayy) >> 6; //pareille mais pour la hauteur
			rting->mp = rting->my * rting->mapx + rting->mx; //trouver la position sur la map
			if (rting->mp > 0 && rting->mp < rting->mapsize
					&& map->recup.tab_map[rting->mp] == 1) /*si la position de la map est plus petit que la taille de la map et que la position de la map est egale a un mur, c'est qu'il y a un mur*/
			{
				hx = rting->rayx; //sauvegarder le rayon de x
				hy = rting->rayy; //sauvegarder le rayon de y
				dish = dist_endray_play(rting->px, rting->py, hx, hy, rayangle)
				dof = rting->mapx; //dof est egale au mur qui determine la fin de la map en x
			}
			else //si on ne touche pas de mur
			{
				rting->rayx += rting->xo; //on doit checker la prochaine ligne horizontal
				rting->rayy += rting->yo; //on doit checker la prochaine ligne verticale
				dof += 1;
			}
		}
		dof = 0;
		disv = 1000000;
		vx = rting->px;
		vy = rting->py;
		ntan = -tan(rting->rayangle);
		if (rayangle > PI2 && rayangle < PI3) /*le rayon regarde a gauche (donc y reste pareille
			et x descend*/
		{
			rting->rayx = (((int)rting->px>>6)<<6) - 0.0001;
			rting->rayy = (ring->px - rting->rayx) * ntan + rting->py;
			rting->xo = -64;
			rting->yo = -rting->xo * ntan;
		}
		if (rayangle < PI2 || rayangle > PI3) /*le de rayon regarde a droite
			(donc reste pareille en y x monte)*/
		{
			rting->rayx = (((int)rting->px>>6)<<6) + 64;
			rting->rayy = (rting->px - rting->rayx) * ntan + rting->py;
			rting->xo = 64;
			rting->yo = -rting->xo * ntan;
		}
		if (rting->rayangle == 0 || rting->rayangle == PI) /*si le rayon regarde a gauche ou a
		droite c'est impossible pour le rayon de toucher une ligne verticale (y)*/
		{
			rting->rayx = rting->px;
			rting->rayy = rting->py;
			dof = rting->mapy;
		}
		while (dof < rting->mapy) /*boucle qui permet de verifier jusqu'a la taille de y*/
		{
			rting->mx = (int)(rting->rayx) >> 6;
			rting->my = (int)(rting->rayy) >> 6;
			rting->mp = rting->my * rting->mapx + rting->mx;
			if (rting->mp > 0 && rting->mp < rting->mapsize
					&& map->recup.tab_map[rting->mp] == 1)
			{
				vx = rting->rayx;
				vy = rting->rayy;
				disv = dist_endray_play(rting->px, rting->py, vx, vy, rayangle)
				dof = rting->mapy;
			}
			else //si on ne touche pas de mur
			{
				rting->rayx += rting->xo;
				rting->rayy += rting->yo;
				dof += 1;
			}
		}
		if (disv < dish) //sauvegarder la plus petite distance - vertical wall hit
		{
			rting->rayx = vx;
			rting->rayy = vy;
			distfinal = disv;
			//peut mettre degrades de couleurs
		}
		if (dish < disv) //sauvegarder la plus petite distance - horizontal wall hit
		{
			rting->rayx = hx;
			rting->rayy = hy;
			distfinal = dish;
			//peut mettre degrades de couleurs
		}
		//appeler la window et draw 3d walls
		double	lineh;
		double	lineo;
		double	ca;
		ca = rting->pangle - rayangle;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		distfinal = distfinal * cos(ca); //fix fisheyes
		lineh = (rting->mapsize * rting->mapx) / distfinal; //line height
		if (lineh > rting->mapx)
			lineh = rting->mapx;
		//draw the line
		lineo = rting->mapy - lineh / 2; //line offset
		ray++;
		rayangle += DR;
		if (rayangle < 0)
			rayangle += 2 * PI;
		if (rayangle > 2 * PI)
			rayangle -= 2 * PI;
	}
}	

static void	process_raycaster(t_rting *rting, t_map *map)
{
	rting->px = (double)map->recup.posx; //player position
	rting->py = (double)map->recup.posy; //player position
	rting->deltapx = cos(rting->pangle) * 5;
	rting->deltapy = sin(rting->pangle) * 5;
	//keys();
	rting->mapx = map->utils.max_index - 1;
	rting->mapy = map->utils.max_line;
	rting->mapsize = rting->mapx * rting->mapy;
	draw_rays2d(rting, map);
}

void	start_graph(t_map *map)
{
	t_graph	graph;
	t_rting rting;

	ft_bzero(&rting, sizeof(rting));
	ft_bzero(&graph, sizeof(graph));
	graph_holder(&graph);
	init_graph(&graph, map);
	process_window(&graph, map);
	process_raycaster(&rting, map);	
	mlx_loop(graph.recup.mlx_ptr);
}
