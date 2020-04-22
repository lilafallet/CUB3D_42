/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 17:09:05 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/22 17:21:14 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	send_to_function_color(t_vector *cpy_vct, char *tab_color[NB_INDIC_COLOR],
							t_state_machine *machine, t_vector *vct)
{
	int		ret;
	int		index;
	size_t	len;	

	ret = is_color(cpy_vct, tab_color);
	index = ret;
	len = vct_getlen(vct);
	if (ret == COLOR_C || ret == COLOR_F)
		ret = TRUE;
	else
		ret = NEXT;
	if (ret == TRUE)
		ret = pre_split_color(cpy_vct, tab_color[index], machine); 
	if (ret == NEXT)
		ret = what_information_color(vct, len, machine, NEXT_OTHERCHAR);
	if (ret == ERROR)
		machine->information |= ERROR_COLOR;
	if (ret == TRUE && (((machine->information & BT_COLOR_F) == FALSE ||
			(machine->information & BT_COLOR_C) == FALSE)))
		ret = ERROR;
	return (ret);
}
