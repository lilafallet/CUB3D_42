/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_resolution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/27 11:14:32 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_number_resolution(t_vector *split, t_state_machine *machine,
								size_t i)
{
	unsigned long	nb;

	if (vct_apply(split, IS_DIGIT) == FALSE)
		machine->information |= ERROR_RESOLUTION_WRONG_TYPE_NUMBER;
	else
	{
		nb = ft_atoul(vct_getstr(split));
		if (nb > INT_MAX)
			machine->information |= ERROR_RESOLUTION_WRONG_TYPE_NUMBER;
		else
			machine->info.str_resolution[i - 1] = vct_apply(split, TO_ATOI);
	}
}

void	is_indic_resolution(t_vector *split, t_state_machine *machine)
{
	if (ft_strequ(vct_getstr(split), "R") == FALSE)
		machine->state = TEXTURE;
	else
	{
		if (machine->information & BT_RESOLUTION)
			machine->information |= ERROR_RESOLUTION_WRONG_TYPE_INDICATOR;
		else
			machine->information |= BT_RESOLUTION;
	}
}
