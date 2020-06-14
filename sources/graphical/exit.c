/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:06:58 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/14 09:32:31 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exitred(t_graph *gr)
{
	t_map *map;

	//mlx_destroy_image(gr->win.mlx_ptr, gr->win.img_ptr);
	//gr->win.img_ptr = NULL;
	map = get_map(NULL);
	free(gr->sp.pos);
	free(gr->sp.raybuff);
	ft_free(map, NULL);
	exit(0);
	return (TRUE);
}
