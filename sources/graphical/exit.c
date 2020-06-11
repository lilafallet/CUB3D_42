/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:06:58 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/11 13:33:53 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_mlx(t_graph *gr, t_map *map)
{
	//free(gr->win.mlx_ptr);
	//free(gr->win.img_ptr);
	//free(gr->win.data);
	//free(gr->win.win_ptr);
	//A RAJOUTER
}

int	exitred(t_graph *gr)
{
	t_map *map;

	map = get_map(NULL);
	free(gr->sp.pos);
	free(gr->sp.raybuff);
	free_mlx(gr, map);
	ft_free(map, NULL);
	printf("hihi\n"); //
	exit(0);
	return (TRUE);
}
