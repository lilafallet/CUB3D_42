/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_utilsmoove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:06:53 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/16 18:03:41 by lfallet          ###   ########.fr       */
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

static int	interior_wall(double tmp_posx, double tmp_posy, t_graph *gr,
							t_map *map)
{
	static int	yp = 0;
	static int	ym = 0;
	static int	xp = 0;
	static int	xm = 0;

	printf("INTERIOR WALL\n"); //
	if (map->recup.tab_map[(int)tmp_posy + 1][(int)tmp_posx] == WALL)
	{
		printf("Y + 1\n"); //
		ym = FALSE;
		xp = FALSE;
		xm = FALSE;
		yp++;
		if (yp == TRUE)
			gr->mv.tmp_yp = (int)tmp_posy + 1;
		printf("tmp_yp = %d\n", gr->mv.tmp_yp); //
		printf("tmp_yp - 0.1 = %lf\n", (double)gr->mv.tmp_yp - 0.1); //
		if (tmp_posy > (double)gr->mv.tmp_yp - 0.1)
		{	
			printf("TRUE YP\n\n"); //
			return (TRUE);
		}
	}
	else if (map->recup.tab_map[(int)tmp_posy - 1][(int)tmp_posx] == WALL)
	{
		printf("Y - 1\n"); //
		yp = FALSE;
		xp = FALSE;
		xm = FALSE;
		ym++;
		if (ym == TRUE)
			gr->mv.tmp_ym = (int)tmp_posy;
		printf("tmp_ym = %d\n", gr->mv.tmp_ym); //
		printf("tmp_ym + 0.1 = %lf\n", (double)gr->mv.tmp_ym + 0.1); //
		printf("tmp_ym + 0.2 = %lf\n", (double)gr->mv.tmp_ym + 0.2); //
		if (tmp_posy >= (double)gr->mv.tmp_ym + 0.1
				&& tmp_posy <= (double)gr->mv.tmp_ym + 0.2)
		{
			printf("TRUE YM\n\n"); //
			return (TRUE);
		}
	}
	if (map->recup.tab_map[(int)tmp_posy][(int)tmp_posx + 1] == WALL)
	{
		printf("X + 1\n"); //
		ym = FALSE;
		yp = FALSE;
		xm = FALSE;
		xp++;	
		if (xp == TRUE)
			gr->mv.tmp_xp = (int)tmp_posx + 1;
		printf("tmp_xp = %d\n", gr->mv.tmp_yp); //
		printf("tmp_xp - 0.1 = %lf\n", (double)gr->mv.tmp_xp - 0.1); //
		if (tmp_posx > (double)gr->mv.tmp_xp - 0.1)
		{
			printf("TRUE XP\n\n"); //
			return (TRUE);
		}
	}
	else if (map->recup.tab_map[(int)tmp_posy][(int)tmp_posx - 1] == WALL)
	{
		printf("X - 1\n"); //
		ym = FALSE;
		yp = FALSE;
		xp = FALSE;
		xm++;
		if (xm == TRUE)
			gr->mv.tmp_xm = (int)tmp_posx;
		printf("tmp_xm = %d\n", gr->mv.tmp_xm); //
		printf("tmp_xm + 0.1 = %lf\n", (double)gr->mv.tmp_xm + 0.1); //
		printf("tmp_xm + 0.2 = %lf\n", (double)gr->mv.tmp_xm + 0.2); //
		if (tmp_posx >= (double)gr->mv.tmp_xm + 0.1
				&& tmp_posx <= (double)gr->mv.tmp_xm + 0.2)
		{
			printf("TRUE XM\n\n"); //
			return (TRUE);
		}
	}
	return (FALSE);
}

int		is_wall(t_graph *gr, t_map *map)
{
	double	tmp_posx;
	double	tmp_posy;
	int		ret;
	
	tmp_posx = gr->mv.new_posx;
	tmp_posy = gr->mv.new_posy;
	printf("tmp_posx = %lf\n", tmp_posx); //
	printf("tmp_posy = %lf\n", tmp_posy); //
	printf("max_line = %zu\n", map->utils.max_line); //
	printf("max_index = %zu\n", map->utils.max_index); //
	ret = exterior_wall(tmp_posx, tmp_posy, gr, map);
	if (ret == TRUE)
		return (TRUE);
	ret = interior_wall(tmp_posx, tmp_posy, gr, map);
	if (ret == TRUE)
		return (TRUE);
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
