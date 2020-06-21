/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:06:58 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/21 11:12:39 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exitred(t_graph *gr)
{
	t_map *map;

	//ATTENTION, PEUT ETRE PAS LA MEME CHOSE DANS LA PARTIE NORMALE
	map = get_map(NULL);
	free(gr->sp.pos);
	free(gr->sp.raybuff);
	free(gr->win.mlx_ptr);
	ft_free(map, NULL);
	exit(0);
	return (TRUE);
}
