/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_resolution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 22:55:47 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_number_resolution(t_vector *split, t_state_machine *map,
								size_t i)
{
	unsigned long	nb;

	if (vct_apply(split, IS_DIGIT) == FALSE)
		map->information |= ERROR_RESOLUTION_WRONG_TYPE_NUMBER;
	else
	{
		nb = ft_atoul(vct_getstr(split));
		if (nb > INT_MAX)
			map->information |= ERROR_RESOLUTION_WRONG_TYPE_NUMBER;
		else
			map->info.str_resolution[i - 1] = vct_apply(split, TO_ATOI);
	}
}

void	is_indic_resolution(t_vector *split, t_state_machine *map)
{
	if (ft_strequ(vct_getstr(split), "R") == FALSE)
		map->state = TEXTURE;
	else
	{
		if (map->information & BT_RESOLUTION)
			map->information |= ERROR_RESOLUTION_WRONG_TYPE_INDICATOR;
		else
			map->information |= BT_RESOLUTION;
	}
}
