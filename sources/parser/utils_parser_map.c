/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 20:59:20 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/19 18:19:51 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int is_wall_or_void(t_state_machine *machine, size_t y, size_t x)
{
	return (machine->info.tab_map[y][x] == VOID ||
				machine->info.tab_map[y][x] == WALL);
}

int	verification_global_map(t_state_machine *machine)
{
	size_t	x;
	size_t	y;
	int		ret;

	y = 0;
	ret = TRUE;
	ft_printf("------------------------ START\n");
	ft_printf("MAX LINE = %d\n", machine->info.max_line); //
	ft_printf("MAX INDEX = %d\n", machine->info.max_index); //
	while (y < machine->info.max_line)
	{
		x = 0;
		while (x < machine->info.max_index)
		{
			if (machine->info.tab_map[y][x] == VOID)
			{
				if ((x != 0 && (is_wall_or_void(machine, y, x - 1) == FALSE)) ||
					(x != machine->info.max_index &&
					(is_wall_or_void(machine, y, x + 1) == FALSE))
					|| (y != 0 && (is_wall_or_void(machine, y - 1, x) == FALSE))
					|| (y != machine->info.max_line &&
					(is_wall_or_void(machine, y + 1, x) == FALSE)))
				{	
						machine->information |= ERROR_MAP;
						ret = ERROR;
						ft_printf("\033[31mERROR\033[0m\n");
						return (ret);
				}
			}
			x++;
		}
		y++;
	}
	ft_printf("RET FINAL =============================================== %d\n", ret); //
	return (ret);
}

int recuperation_eachelem(t_state_machine *machine, size_t count_line, size_t index, int flag)
{
	static size_t	tmp_index = 0;
	int				ret; 
	
	ret = TRUE;
	if (index != tmp_index + 1 && index != 0)
		return (ERROR);
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
	size_t	index_end;
	size_t	index_start;

	ret = TRUE;
	len = vct_getlen(line);
	index_end = len - 1;
	index_start = 0;
	if (count_line == 0)
	{
		while (index_start < len)
		{
			if (machine->info.tab_map[count_line][index_start] != OUT && 
					machine->info.tab_map[count_line][index_start] != WALL && 
					machine->info.tab_map[count_line][index_start] != VOID) 
				return (ERROR);
			index_start++;
		}	
	}
	if (machine->info.tab_map[count_line][index_end] != OUT &&
			machine->info.tab_map[count_line][index_end] != WALL)
		ret = ERROR;
	else if (machine->info.tab_map[count_line][index_end] == OUT)
	{
		while (machine->info.tab_map[count_line][index_end] == OUT)
			index_end--;
		if (machine->info.tab_map[count_line][index_end] != WALL)
			ret = ERROR;
	}
	return (ret);
}
