/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:52:06 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/27 00:20:22 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_graph *gr, t_map *map)
{
	printf("posy = %lf\n", gr->mv.new_posy); //
	printf("posx = %lf\n", gr->mv.new_posx); //
	return (map->recup.tab_map[(int)gr->mv.new_posy][(int)gr->mv.new_posx]
									== WALL ? TRUE : FALSE);
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
