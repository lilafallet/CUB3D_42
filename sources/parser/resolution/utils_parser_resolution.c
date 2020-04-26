/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_resolution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/26 10:36:54 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_number_resolution(t_vector *split, t_state_machine *machine,
								size_t i)
{
	if (vct_apply(split, IS_DIGIT) == FALSE)
		machine->information |= ERROR_RESOLUTION;
	else
		machine->info.str_resolution[i - 1] = vct_apply(split, TO_ATOI);
}

void	is_indic_resolution(t_vector *split, t_state_machine *machine)
{
	if (ft_strequ(vct_getstr(split), "R") == FALSE)
		machine->state = TEXTURE;
	else
	{
		if (machine->information & BT_RESOLUTION)
			machine->information |= ERROR_RESOLUTION;
		else
			machine->information |= BT_RESOLUTION;
	}
}
