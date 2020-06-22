/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_utilsmoove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:06:53 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/22 15:45:49 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_wall_or_sprite(t_map *map, double y, double x)
{
	return (map->recup.tab_map[(int)y][(int)x] == WALL
			|| map->recup.tab_map[(int)y][(int)x] == SPRITE);
}

int		is_posx_into_wall(t_graph *gr, t_map *map)
{
	const double pad = gr->mv.speed_mv + MIN_PAD;

	if ((size_t)(gr->mv.old_posx + pad) >= map->utils.max_index - 1
		|| (size_t)(gr->mv.new_posx) >= map->utils.max_index - 1)
		return (TRUE);
	if ((int)(gr->mv.old_posx - pad) < 0 || (int)(gr->mv.new_posx) < 0)
		return (TRUE);
	return (is_wall_or_sprite(map, gr->mv.new_posy,
			(gr->mv.new_posx > gr->mv.old_posx) ?
				gr->mv.old_posx + pad : 
				gr->mv.old_posx - pad));
}

int		is_posy_into_wall(t_graph *gr, t_map *map)
{
	const double pad = gr->mv.speed_mv + MIN_PAD;

	if ((size_t)(gr->mv.old_posy + pad) >= map->utils.max_line
		|| (size_t)(gr->mv.new_posy) >= map->utils.max_line)
		return (TRUE);
	if ((int)(gr->mv.old_posy - pad) < 0 || (int)(gr->mv.new_posy) < 0)
		return (TRUE);
	return (is_wall_or_sprite(map, (gr->mv.new_posy > gr->mv.old_posy) ?
					gr->mv.old_posy + pad : 
					gr->mv.old_posy - pad,
						 gr->mv.new_posx));
}

int		is_wall(t_graph *gr, t_map *map)
{
	if (is_posy_into_wall(gr, map) == TRUE)
		gr->mv.new_posy = gr->mv.old_posy;
	if (is_posx_into_wall(gr, map) == TRUE)
		gr->mv.new_posx = gr->mv.old_posx;
	return (FALSE); 
}

int	update(t_graph *gr)
{
	return (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN || gr->mv.log & MV_LEFT
			|| gr->mv.log & MV_RIGHT || gr->mv.log & LK_LEFT
			|| gr->mv.log & LK_RIGHT ? TRUE : FALSE);
}

void	look_right(t_graph *gr, double tmp_dirx, double tmp_planecamx)
{
	//ft_printf("FONCTION LOOK RIGHT\n"); //
	gr->mv.log |= CAM;
	/*ajoute le fait qu'il va y avoir une rotation*/
	gr->rting.dirx = gr->rting.dirx * cos(gr->mv.speed_lk) - gr->rting.diry
						* sin(gr->mv.speed_lk);
	gr->rting.diry = tmp_dirx * sin(gr->mv.speed_lk) + gr->rting.diry
						* cos(gr->mv.speed_lk);
	gr->rting.planecamx = gr->rting.planecamx * cos(gr->mv.speed_lk)
							- gr->rting.planecamy * sin(gr->mv.speed_lk);
	gr->rting.planecamy = tmp_planecamx * sin(gr->mv.speed_lk)
							+ gr->rting.planecamy * cos(gr->mv.speed_lk);
	/*cos = deplacements en x / sin = deplacements en y*/
}

void	look_left(t_graph *gr, double tmp_dirx, double tmp_planecamx)
{
	//ft_printf("FONCTION LOOK LEFT\n"); //
	gr->mv.log |= CAM;
	/*ajoute le fait qu'il va y avoir une rotation*/
	gr->rting.dirx = gr->rting.dirx * cos(-gr->mv.speed_lk) - gr->rting.diry
						* sin(-gr->mv.speed_lk);
	gr->rting.diry = tmp_dirx * sin(-gr->mv.speed_lk) + gr->rting.diry
						* cos(-gr->mv.speed_lk);
	gr->rting.planecamx = gr->rting.planecamx * cos(-gr->mv.speed_lk)
							- gr->rting.planecamy * sin(-gr->mv.speed_lk);
	gr->rting.planecamy = tmp_planecamx * sin(-gr->mv.speed_lk)
							+ gr->rting.planecamy * cos(-gr->mv.speed_lk);
	/*cos = deplacements en x / sin = deplacements en y / SPEED negt car on va
	vers la gauche*/
}
