/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_utilsmoove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:06:53 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/17 14:31:40 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	exterior_wall(double tmp_posx, double tmp_posy,
							t_graph *gr, t_map *map)
{
	printf("EXTERIOR WALL\n"); //
	if ((int)tmp_posy == map->utils.max_line - 1 
		|| (int)tmp_posx == map->utils.max_index - 2)
		return (TRUE);
	if (tmp_posy >= 1.1 && tmp_posy <= 1.2)
		return (TRUE); //
	if (tmp_posx >= 1.1 && tmp_posx <= 1.2)
		return (TRUE); //
	if (tmp_posy < 1.000000)
	{
		gr->mv.new_posy = 1.1;
		return (TRUE);
	}
	if (tmp_posx < 1.000000)
	{
		gr->mv.new_posx = 1.1;
		return (TRUE);
	}
	printf("\n"); //
	return (FALSE);
}

int		is_wall(t_graph *gr, t_map *map)
{
	if ((gr->mv.new_posy > gr->mv.old_posy
		&& (size_t)(gr->mv.old_posy + SPEED_MV) < map->utils.max_line
		&& (map->recup.tab_map[(int)(gr->mv.old_posy + SPEED_MV)][(int)gr->mv.new_posx] == WALL
			|| map->recup.tab_map[(int)(gr->mv.old_posy + SPEED_MV)][(int)gr->mv.new_posx] == SPRITE))
		|| (gr->mv.new_posy < gr->mv.old_posy && (int)(gr->mv.old_posy - SPEED_MV) >= 0
		&& (map->recup.tab_map[(int)(gr->mv.old_posy - SPEED_MV)][(int)gr->mv.new_posx] == WALL
			|| map->recup.tab_map[(int)(gr->mv.old_posy - SPEED_MV)][(int)gr->mv.new_posx] == SPRITE)))
	{
		
		if (map->recup.tab_map[(int)(gr->mv.old_posy + SPEED_MV)][(int)gr->mv.new_posx] == SPRITE
			|| map->recup.tab_map[(int)(gr->mv.old_posy - SPEED_MV)][(int)gr->mv.new_posx] == SPRITE) //BONUS
		{
			gr->lf.is_sprite = TRUE;
			if (gr->lf.firsty == FALSE)
				gr->lf.firsty++;
			gr->lf.count_outsprite = -1;
			printf("SPRITE Y\n"); //
		}
		//printf("gr->mv.new_posy = %lf\n", gr->mv.new_posy); //
		gr->mv.new_posy = gr->mv.old_posy;
	}
	if ((gr->mv.new_posx > gr->mv.old_posx
		&& (size_t)(gr->mv.old_posx + SPEED_MV) < map->utils.max_index - 1
		&& (map->recup.tab_map[(int)gr->mv.new_posy][(int)(gr->mv.old_posx + SPEED_MV)] == WALL
			|| map->recup.tab_map[(int)gr->mv.new_posy][(int)(gr->mv.old_posx + SPEED_MV)] == SPRITE))
		|| (gr->mv.new_posx < gr->mv.old_posx && (int)(gr->mv.old_posx - SPEED_MV) >= 0
		&& (map->recup.tab_map[(int)gr->mv.new_posy][(int)(gr->mv.old_posx - SPEED_MV)] == WALL
			|| map->recup.tab_map[(int)gr->mv.new_posy][(int)(gr->mv.old_posx - SPEED_MV)] == SPRITE)))
	{
		if (map->recup.tab_map[(int)gr->mv.new_posy][(int)(gr->mv.old_posx + SPEED_MV)] == SPRITE
			|| map->recup.tab_map[(int)gr->mv.new_posy][(int)(gr->mv.old_posx - SPEED_MV)] == SPRITE) //BONUS
		{
			if (gr->lf.firstx == FALSE)
				gr->lf.firstx++;
			gr->lf.count_outsprite = -1;
			printf("SPRITE X\n"); //
		}
		//printf("gr->mv.new_posx = %lf\n", gr->mv.new_posx); //
		gr->mv.new_posx = gr->mv.old_posx;
	}
	if ((size_t)gr->mv.new_posy >= map->utils.max_line)
		gr->mv.new_posy = (double)map->utils.max_line - SPEED_MV;
	if ((int)gr->mv.new_posy < 0)
		gr->mv.new_posy = SPEED_MV;
	if ((size_t)gr->mv.new_posx >= map->utils.max_index - 1)
		gr->mv.new_posx = (double)map->utils.max_index - 1 - SPEED_MV;
	if ((int)gr->mv.new_posx < 0)
		gr->mv.new_posx = SPEED_MV;
	if (map->recup.tab_map[(int)gr->mv.new_posy][(int)gr->mv.new_posx] == WALL
		|| map->recup.tab_map[(int)gr->mv.new_posy][(int)gr->mv.new_posy] == SPRITE)
	{
		gr->mv.new_posy = gr->mv.old_posy;
		gr->mv.new_posx = gr->mv.old_posx;
	}
	if (gr->lf.firstx == TRUE || gr->lf.firsty == TRUE)
	{
		gr->lf.count_outsprite++;
		printf("count out sprite = %zu\n", gr->lf.count_outsprite); //
	}
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
	gr->rting.dirx = gr->rting.dirx * cos(SPEED_LK) - gr->rting.diry
						* sin(SPEED_LK);
	gr->rting.diry = tmp_dirx * sin(SPEED_LK) + gr->rting.diry
						* cos(SPEED_LK);
	gr->rting.planecamx = gr->rting.planecamx * cos(SPEED_LK)
							- gr->rting.planecamy * sin(SPEED_LK);
	gr->rting.planecamy = tmp_planecamx * sin(SPEED_LK)
							+ gr->rting.planecamy * cos(SPEED_LK);
	/*cos = deplacements en x / sin = deplacements en y*/
}

void	look_left(t_graph *gr, double tmp_dirx, double tmp_planecamx)
{
	//ft_printf("FONCTION LOOK LEFT\n"); //
	gr->mv.log |= CAM;
	/*ajoute le fait qu'il va y avoir une rotation*/
	gr->rting.dirx = gr->rting.dirx * cos(-SPEED_LK) - gr->rting.diry
						* sin(-SPEED_LK);
	gr->rting.diry = tmp_dirx * sin(-SPEED_LK) + gr->rting.diry
						* cos(-SPEED_LK);
	gr->rting.planecamx = gr->rting.planecamx * cos(-SPEED_LK)
							- gr->rting.planecamy * sin(-SPEED_LK);
	gr->rting.planecamy = tmp_planecamx * sin(-SPEED_LK)
							+ gr->rting.planecamy * cos(-SPEED_LK);
	/*cos = deplacements en x / sin = deplacements en y / SPEED negt car on va
	vers la gauche*/
}
