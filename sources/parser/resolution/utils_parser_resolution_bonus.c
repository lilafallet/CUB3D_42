/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_resolution_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:21:17 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:21:18 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	is_number_resolution(t_vector *split, t_state_machine *machine,
								size_t i, t_map *map)
{
	unsigned long	nb;

	if (vct_apply(split, IS_DIGIT) == FALSE)
		machine->info |= ERROR_RESOLUTION_WRONG_TYPE_NUMBER;
	else
	{
		nb = ft_atoul(vct_getstr(split));
		if (nb > INT_MAX || nb <= 0)
			machine->info |= ERROR_RESOLUTION_WRONG_TYPE_NUMBER;
		else
			map->recup.resolution[i - 1] = vct_apply(split, TO_ATOI);
	}
	map->utils.count_resolution++;
}

void	is_indic_resolution(t_vector *split, t_state_machine *machine)
{
	if (ft_strequ(vct_getstr(split), STR_RESOLUTION) == FALSE)
		machine->state = TEXTURE;
	else
	{
		if (machine->info & BT_RESOLUTION)
			machine->info |= ERROR_RESOLUTION_WRONG_TYPE_INDICATOR;
		else
			machine->info |= BT_RESOLUTION;
	}
}
