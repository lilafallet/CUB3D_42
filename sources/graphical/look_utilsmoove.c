/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_utilsmoove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:06:53 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/15 15:16:53 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_graph *gr, t_map *map)
{
	double	tmp_posx;
	double	tmp_posy;

	if (gr->mv.y == 10 && (gr->mv.log & MV_UP) == FALSE)
		gr->mv.y = 0;
	tmp_posx = gr->mv.new_posx;
	tmp_posy = gr->mv.new_posy;
	printf("tmp_posx = %lf\n", tmp_posx); //
	printf("tmp_posy = %lf\n", tmp_posy); //
	printf("tmp_posx = %d\n", (int)tmp_posx); //
	printf("tmp_posy = %d\n", (int)tmp_posy); //
	printf("floor(tmp_posx) = %lf\n", floor(tmp_posx)); //
	printf("floor(tmp_posx - SPEED_MV) = %lf\n", floor(tmp_posx - SPEED_MV)); //
	if ((int)tmp_posy == 1 && gr->mv.y < 10)
	{
		printf("HERE\n"); //
		gr->mv.y++;
	}
	printf("y = %d\n\n", gr->mv.y); //
	if (((int)tmp_posx > 0
		&& (gr->mv.log & MV_DOWN || gr->mv.log & MV_UP)
		&& floor(tmp_posx) != floor(tmp_posx - SPEED_MV)))
	{
		printf("POSX\n"); //
		/*si pas dans un mur + DOWN + la position actuelle est different de la
		prochaine position = position actuelle == la prochaine position*/
		tmp_posx -= SPEED_MV;
		printf("new_tmpposx = %lf\n", tmp_posx); //
		//permet de ne pas rentrer dans la texture
	}
	if (((int)tmp_posy > 0
		&& (gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT)
		&& floor(tmp_posy) != floor(tmp_posy - SPEED_MV)) || gr->mv.y == 10)
	{
		
		printf("POSY\n"); //
		/*si pas dans un mur + LEFT + la position actuelle est different de la
		prochaine position = position actuelle == la prochaine position*/
		tmp_posy -= SPEED_MV;
		//permet de ne pas rentrer dans la texture
	}
	if ((int)tmp_posy == 1 && gr->mv.y == 10 && gr->mv.log & MV_UP
			&& tmp_posy == 1.000000)
	{
		printf("RETURN TRUE\n"); //
		return (TRUE);
	}
	if (map->recup.tab_map[(int)tmp_posy][(int)tmp_posx] == WALL)
	{
		printf("IS_WALL\n");
		return (TRUE);
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
