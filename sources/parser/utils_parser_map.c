/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 20:59:20 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/17 22:01:56 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	recuperation_void(t_vector *vct, t_state_machine *machine, size_t count_line, size_t index)
{
	int ret;
	size_t	len;
	size_t	size;

	ft_printf("FONCTION VOID\n");	
	ret = TRUE;
	len = vct_getlen(vct);
	size = index + len;
	while (index < size)
	{
		machine->info.tab_map[count_line][index] = VOID;
		printf("RECUPERATION_VOID -> machine->info.tab_map[%zu][%zu] = %d\n",
				count_line, index, machine->info.tab_map[count_line][index]); //
		index++;
	}
	return (ret);
}

int	recuperation_wall(t_vector *vct, t_state_machine *machine, size_t count_line, size_t index)
{
	int ret;
	size_t	len;
	size_t	size;

	ft_printf("FONCTION WALL\n");	
	ret = TRUE;
	len = vct_getlen(vct);
	size = index + len;
	while (index < size)
	{
		machine->info.tab_map[count_line][index] = WALL;
		printf("RECUPERATION_WALL -> machine->info.tab_map[%zu][%zu] = %d\n",
				count_line, index, machine->info.tab_map[count_line][index]); //
		index++;
	}
	return (ret);
}

int	recuperation_sprite(t_vector *vct, t_state_machine *machine, size_t count_line, size_t index)
{
	int ret;
	size_t	len;
	size_t	size;

	ft_printf("FONCTION SPRITE\n");	
	ret = TRUE;
	len = vct_getlen(vct);
	size = index + len;
	while (index < size)
	{
		machine->info.tab_map[count_line][index] = SPRITE;
		printf("RECUPERATION_SPRITE -> machine->info.tab_map[%zu][%zu] = %d\n",
				count_line, index, machine->info.tab_map[count_line][index]); //
		index++;
	}
	return (ret);
}

int	recuperation_position(t_vector *vct, t_state_machine *machine, size_t count_line, size_t index)
{
	int ret;
	size_t	len;
	size_t	size;

	ft_printf("FONCTION POSITION\n");	
	ret = TRUE;
	len = vct_getlen(vct);
	size = index + len;
	while (index < size)
	{
		machine->info.tab_map[count_line][index] = POSITION;
		printf("RECUPERATION_POSITION -> machine->info.tab_map[%zu][%zu] = %d\n",
				count_line, index, machine->info.tab_map[count_line][index]); //
		index++;
	}
	return (ret);
}
