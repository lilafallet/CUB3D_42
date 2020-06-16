/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_utilsmoove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:06:53 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/16 14:19:53 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_graph *gr, t_map *map)
{
	double	tmp_posx;
	double	tmp_posy;
	int		left;
	int		down;
	
	tmp_posx = gr->mv.new_posx;
	tmp_posy = gr->mv.new_posy;
	printf("tmp_posx = %lf\n", tmp_posx); //
	printf("tmp_posy = %lf\n", tmp_posy); //
	printf("max_line = %zu\n", map->utils.max_line); //
	printf("max_index = %zu\n", map->utils.max_index); //
	if (map->recup.dirpos == SOUTH)
	{
		if ((int)tmp_posy == map->utils.max_line - 1 
			|| (int)tmp_posx == map->utils.max_index - 2)
		{
			printf("SOUTH TRUE MAX\n\n"); //
			return (TRUE);
		}
		if (tmp_posy >= 1.1 && tmp_posy <= 1.2)
		{
			printf("COUCOU\n"); //
			return (TRUE); //
		}
	}
	printf("\n"); //
	return (FALSE); 
	/*if (gr->mv.log & MV_LEFT)
	{
		printf("MV_LEFT\n"); //
		left = TRUE;
		gr->mv.tmp_left += left;
	}
	if (gr->mv.log & MV_DOWN)
	{
		printf("MV_LEFT\n"); //
		down = TRUE;
		gr->mv.tmp_down += down;
	}
	if (gr->mv.tmp_left != 0 && gr->mv.log & MV_RIGHT)
	{
		printf("TMP_LEFT\n"); //
		gr->mv.tmpl = gr->mv.tmp_left;
		gr->mv.tmp_left = 0;
	}
	if (gr->mv.tmp_down != 0 && gr->mv.log & MV_UP)
	{
		printf("TMP_DOWN\n"); //
		gr->mv.tmpd = gr->mv.tmp_down;
		gr->mv.tmp_down = 0;
	}
	if (gr->mv.ydown == 10 && (gr->mv.log & MV_UP) == FALSE)
	{
		printf("STOPY DOWN\n"); //
		gr->mv.stopydown = FALSE;
		gr->mv.ydown = 0;
	}
	if ((int)tmp_posy == 1 && gr->mv.yup < 10 && (gr->mv.log & MV_UP))
	{
		gr->mv.yup++;
		printf("YUP ++\n"); //
		if (gr->mv.stopyup == TRUE)
		{
			printf("YUP = YUP\n\n"); //
			gr->mv.yup = gr->mv.yup;
			return (TRUE); 
		}
	}
	if ((int)tmp_posx == 1 && gr->mv.xright < 10 && (gr->mv.log & MV_RIGHT))
	{
		gr->mv.xright++;
		printf("XRIGHT ++\n"); //
		if (gr->mv.stopxright == TRUE)
		{
			printf("XRIGHT = XRIGHT\n\n"); //
			gr->mv.xright = gr->mv.xright;
			return (TRUE);
		}
	}
	if (gr->mv.log & MV_RIGHT && gr->mv.tmpl == gr->mv.xright && gr->mv.xright != 0)
	{
		printf("STOPY XRIGHT\n\n"); //
		gr->mv.stopxright = TRUE;
		return (TRUE);
	}
	if (gr->mv.log & MV_UP && gr->mv.tmpd == gr->mv.yup && gr->mv.yup != 0)
	{
		printf("STOPY YUP\n\n"); //
		gr->mv.stopyup = TRUE;
		return (TRUE);
	}
	if (((int)tmp_posx > 0
		&& (gr->mv.log & MV_DOWN || gr->mv.log & MV_UP)
		&& floor(tmp_posx) != floor(tmp_posx - SPEED_MV)))
	{
		printf("POSX\n"); //
		*si pas dans un mur + DOWN + la position actuelle est different de la
		prochaine position = position actuelle == la prochaine position
		tmp_posx -= SPEED_MV;
		//permet de ne pas rentrer dans la texture
	}
	if (((int)tmp_posy > 0
		&& (gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT)
		&& floor(tmp_posy) != floor(tmp_posy - SPEED_MV)))
	{
		printf("POSY\n"); //
	*si pas dans un mur + LEFT + la position actuelle est different de la
		prochaine position = position actuelle == la prochaine position
		tmp_posy -= SPEED_MV;
		//permet de ne pas rentrer dans la texture
	}
	if (map->recup.tab_map[(int)tmp_posy][(int)tmp_posx] == WALL)
	{
		printf("IS_WALL\n\n");
		return (TRUE);
	}
	printf("\n"); //
	return (FALSE);*/
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
