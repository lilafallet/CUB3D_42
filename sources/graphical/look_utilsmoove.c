/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_utilsmoove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:06:53 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/15 20:40:04 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_graph *gr, t_map *map)
{
	double	tmp_posx;
	double	tmp_posy;
	double	tmpx;
	int		left;
	

	if (gr->mv.log & MV_LEFT)
	{
		left = TRUE;
		gr->mv.tmp_left += left;
		printf("left = %d\n", left); //
	}
	printf("tmp_left = %d\n", gr->mv.tmp_left); //
	if (gr->mv.tmp_left != 0 && gr->mv.log & MV_RIGHT)
	{
		printf("COUCOU\n"); //
		gr->mv.tmp = gr->mv.tmp_left;
		gr->mv.tmp_left = 0;
	}
	if (gr->mv.y == 10 && (gr->mv.log & MV_UP) == FALSE)
	{
		gr->mv.stopy = FALSE;
		gr->mv.y = 0;
	}
	if (gr->mv.x == 10
			&& ((gr->mv.log & MV_LEFT && (gr->mv.log & MV_RIGHT) == FALSE)
			|| ((gr->mv.log & MV_RIGHT && (gr->mv.log & MV_RIGHT) == FALSE))))
	{
		printf("HERE\n"); //
		gr->mv.stopx = FALSE;
		gr->mv.x = 0;
	}
	tmp_posx = gr->mv.new_posx;
	tmp_posy = gr->mv.new_posy;
	printf("tmp_posx = %lf\n", tmp_posx); //
	printf("tmp_posy = %lf\n", tmp_posy); //
	printf("tmp_posx = %d\n", (int)tmp_posx); //
	printf("tmp_posy = %d\n", (int)tmp_posy); //
	printf("floor(tmp_posx) = %lf\n", floor(tmp_posx)); //
	printf("floor(tmp_posx - SPEED_MV) = %lf\n", floor(tmp_posx - SPEED_MV)); //
	printf("tmpx = %lf\n", tmpx); //
	printf("tmp = %d\n", gr->mv.tmp); //
	if ((int)tmp_posy == 1 && gr->mv.y < 10)
	{
		printf("HERE Y\n"); //
		gr->mv.y++;
	}
	printf("y = %d\n\n", gr->mv.y); //
	if ((int)tmp_posx == 1 && gr->mv.x < 10 && (gr->mv.log & MV_RIGHT))
	{
		printf("HERE X\n"); //
		gr->mv.x++;
		if (gr->mv.stopx == TRUE)
		{
			gr->mv.x = gr->mv.x;
			return (TRUE);
		}
	}
	printf("x = %d\n\n", gr->mv.x); //
	if (gr->mv.log & MV_RIGHT && gr->mv.tmp == gr->mv.x && gr->mv.x != 0)
	{
		printf("PITIEEEE\n"); //
		gr->mv.stopx = TRUE;
		//return (TRUE);
	}
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
	if ((int)tmp_posy == 1 && gr->mv.y == 10 && (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
			&& floor(tmp_posy - SPEED_MV) == 0.000000)
	{
		printf("RETURN TRUE Y\n"); //
		gr->mv.stopy = TRUE;
		return (TRUE);
	}
	if ((int)tmp_posx == 1 && gr->mv.x == 10 && (gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT)
			&& floor(tmp_posx - SPEED_MV) == 0.000000)
	{
			printf("RETURN TRUE X\n"); //
			gr->mv.stopx = TRUE;
			return (TRUE);
	}
	if (gr->mv.y != 10
		&& map->recup.tab_map[(int)tmp_posy - 1][(int)tmp_posx] == WALL
		/*&& gr->mv.y == 10 - ((int)tmp_posy - 1)*/ && (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN))
	{
		printf("JE VEUX QUE CA RENTRE LA\n");
		gr->mv.y++;
		if (gr->mv.y == 10)
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
