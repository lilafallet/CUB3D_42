/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:05:38 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/24 17:53:19 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	split_resolution(t_vector *resol, char **str_resolution, t_vector *vct)
{
	int	ret;
	int	count;

	ret = NEXT | TRUE;
	count = 0;
	while ((resol = vct_split(vct, STRING_SPACE_TAB, ALL_SEP)) != NULL)
	{
		if (vct_apply(resol, IS_DIGIT) == TRUE) 
		{
			count++;
			ret = count_num(str_resolution, resol);
			if (ret == ERROR)
				break ;
		}
		else if (is_invalid_char(is_invalid_char(resol)) == TRUE)
		{
			ret = ERROR;
			break ;
		}
		vct_del(&resol);
	}
	if (count != NB_RESOLUTION)
		ret = ERROR;
	vct_del(&resol);
	return (ret);
}

int	init_machine_resolution(t_state_machine *machine, int ret)
{
	machine->state = TEXTURE;
	if (ret & TRUE)
	{
		ret &= ~NEXT;
		machine->information |= BT_RESOLUTION;
	}
	if (machine->information & BT_RESOLUTION &&
			machine->information & BT_COLOR_F &&
			machine->information & BT_COLOR_C && machine->information & BT_NO
			&& machine->information & BT_SO && machine->information & BT_WE
			&& machine->information & BT_EA && machine->information & BT_SPR)
	{
		ret = TRUE;
		machine->state = MAP;
	}
	return (ret);
}
