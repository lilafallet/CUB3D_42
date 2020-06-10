/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:06:58 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/10 17:55:21 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_cpytab(t_graph *gr, t_map *map)
{

}

void	free_raybuff(t_graph *gr, t_map *map)
{

}

void	free_spdist(t_graph *gr)
{

}

void	free_sppos(t_graph *gr)
{

}

int	exitred(t_graph *gr)
{
	t_map *map;

	map = get_map(NULL);
	free_sppos(gr);
	free_spdist(gr);
	free_raybuff(gr, map);
	free_cpytab(gr, map);
	ft_free(map, NULL);
	printf("hihi\n"); //
	exit(0);
	return (TRUE);
}
