/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 20:59:20 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/18 19:04:34 by lfallet          ###   ########.fr       */
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
	if (flag == OUT)
		machine->info.tab_map[count_line][index] = OUT;
	printf("[%zu][%zu] = %d\n", count_line, index, machine->info.tab_map[count_line][index]);
	return (TRUE);
}

int	verif_line(t_vector *line, t_state_machine *machine, size_t count_line)
{
	int	ret;
	size_t	len;

	ret = TRUE;
	len = vct_getlen(line);
	printf("VERIF_LINE -> len = %zu\n", len); //
	if (machine->info.tab_map[count_line][len - 1] != OUT &&
			machine->info.tab_map[count_line][len - 1] != WALL)
		ret = ERROR;
	else if (machine->info.tab_map[count_line][len - 1] == OUT)
	{
		while (machine->info.tab_map[count_line][len - 1] == OUT)
			len--;
		if (machine->info.tab_map[count_line][len - 1] != WALL)
			ret = ERROR;
	}
	ft_printf("VERIF_LINE -> ret = %d\n", ret); //
	return (ret);
}
