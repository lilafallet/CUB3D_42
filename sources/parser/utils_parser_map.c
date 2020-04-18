/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 20:59:20 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/18 17:21:23 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int recuperation_eachelem(t_state_machine *machine, size_t count_line, size_t index, int flag)
{
	static size_t	tmp_index = 0;
	int				ret; 
	
	ret = TRUE;
	if (index != tmp_index + 1 && index != 0)
	{
		machine->information |= ERROR_MAP;
		return (ERROR);
	}
	tmp_index = index;
	if (flag == VOID)
		machine->info.tab_map[count_line][index] = VOID;
	if (flag == WALL)
		machine->info.tab_map[count_line][index] = WALL;
	if (flag == SPRITE)
		machine->info.tab_map[count_line][index] = SPRITE;
	if (flag == POSITION)
		machine->info.tab_map[count_line][index] = POSITION;
	printf("[%zu][%zu] = %d\n", count_line, index, machine->info.tab_map[count_line][index]);
	return (TRUE);
}
