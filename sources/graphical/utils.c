/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:52:06 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/27 20:33:51 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_graph *gr, t_map *map)
{
	double	tmp_posx;
	double	tmp_posy;

	tmp_posx = gr->mv.new_posx;
	tmp_posy = gr->mv.new_posy;
	if ((int)tmp_posx > 0
		&& (gr->mv.log & MV_DOWN)
		&& floor(tmp_posx) != floor(tmp_posx - SPEED_MV))
		tmp_posx -= SPEED_MV;
	if ((int)tmp_posy > 0
		&& (gr->mv.log & MV_LEFT)
		&& floor(tmp_posy) != floor(tmp_posy - SPEED_MV))
		tmp_posy -= SPEED_MV;
	if (map->recup.tab_map[(int)tmp_posy][(int)tmp_posx] == WALL)
		return (TRUE);
	return (FALSE);
}

t_graph	*gr_holder(t_graph *gr)
{
	static t_graph	*gr_keep;

	if (gr_keep == NULL && gr != NULL)
		gr_keep = gr;
	return (gr_keep);
}

int	get_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
