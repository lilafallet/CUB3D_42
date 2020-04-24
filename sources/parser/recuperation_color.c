/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recuperation_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:09:03 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/24 17:10:21 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hub_recuperation_color(t_vector *color, char type_color,
								t_state_machine *machine)
{
	int				ret;
	int				num;
	static size_t	index = 0;
	
	ret = TRUE;
	num = ft_atoi(vct_getstr(color));
	if (num < 0 || num > 255)
		ret = ERROR;
	ret = recuperation_color(type_color,machine, num, &index);
	if (index == NB_COLOR && ret != ERROR)
	{
		if (type_color == 'F')
			machine->information |= BT_COLOR_F;	
		else
			machine->information |= BT_COLOR_C;	
		if (have_all_color(machine) == TRUE)
			machine->state = MAP;
		index = 0;
	}
	if (have_all_info(machine) == TRUE)
	{
		ret = TRUE;
		machine->state = MAP;
	}
	return (ret);
}

int	recuperation_color(char type_color, t_state_machine *machine,
								int num, size_t *index)
{
	int	ret;

	if (type_color == 'F')
	{
		machine->info.tab_color_f[*index] = num;
		printf("RECUPERATION_COLOR -> machine->info.tab_color_f[%zu] = %d\n",
				*index, machine->info.tab_color_f[*index]); //
		ret = TRUE;
		*index = *index + 1;
	}
	else
	{
		machine->info.tab_color_c[*index] = num;
		printf("RECUPERATION_COLOR -> machine->info.tab_color_f[%zu] = %d\n",
				*index, machine->info.tab_color_c[*index]); //
		ret = TRUE;
		*index = *index + 1;
	}
	return (ret);
}
