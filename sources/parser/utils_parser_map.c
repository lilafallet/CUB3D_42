/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 20:59:20 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/18 22:15:24 by lfallet          ###   ########.fr       */
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

	ret = TRUE;
	len = vct_getlen(line);
	index_end = len - 1;
	printf("VERIF_LINE -> len = %zu\n", len); //
	if (machine->info.tab_map[count_line][index_end] != OUT &&
			machine->info.tab_map[count_line][index_end] != WALL)
	{
		ft_printf("VERIF_LINE -> dernier char est invalide\n"); //
		ret = ERROR;
	}
	else if (machine->info.tab_map[count_line][index_end] == OUT)
	{
		ft_printf("VERIF_LINE -> dernier char est OUT (4)\n"); //
		while (machine->info.tab_map[count_line][index_end] == OUT)
		{
			ft_printf("VERIF_LINE -> tant que char est OUT (4) on diminue\n"); //
			printf("VERIF_LINE WHILE -> index_end BEGIN = %zu\n", index_end);
			index_end--;
			printf("VERIF_LINE WHILE-> index_end = %zu\n", index_end);
		}
		ft_printf("%d\n", machine->info.tab_map[count_line][index_end]); //
		printf("VERIF_LINE -> index_end = %zu\n", index_end);
		if (machine->info.tab_map[count_line][index_end] != WALL)
		{
			ft_printf("VERIF_LINE -> si le char sur lequel on tombe est different de WALL (1), le retour == ERROR\n"); //
			ret = ERROR;
		}
	}
	ft_printf("VERIF_LINE -> ret = %d\n", ret); //
	return (ret);
}
