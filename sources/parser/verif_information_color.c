/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_information_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:11:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/24 17:32:33 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verif_before_color(t_vector *vct, size_t clen, t_state_machine *machine)
{
	size_t	i;
	char	*str;
	int		ret;

	i = 0;
	str = vct_getstr(vct);
	ret = TRUE;
	while (i < clen)
	{
		if (str[i] != SPACE && str[i] != TAB)
		{
			ret = what_information_color(vct, clen, machine, ret);
			if (ret == NEXT)
				break ;
		}
		i++;
	}
	return (ret);
}

int	is_color(t_vector *vct, char **tab_color)
{
	int	index;
	char	*str;

	index = 0;
	str = NULL;
	while (index < NB_INDIC_COLOR)
	{
		str = ft_strnstr(vct_getstr(vct), tab_color[index], vct_getlen(vct));
		if (str != NULL)
			break ;
		index++;
	}
	return (index);
}

int	error_or_true(t_vector *color, size_t count_loops, size_t count_num)
{
	int				ret;

	ret = TRUE;
	if ((count_loops == 0 || count_loops == 6) &&
			vct_apply(color, IS_WHITESPACE) == FALSE)
		ret = ERROR;
	else if (count_loops == 1 && vct_apply(color, IS_DIGIT) == FALSE)
		ret = ERROR;
	else if ((count_loops == 2 || count_loops == 4) && vct_apply(color,
				IS_WHITESPACECOMMA) == FALSE)
		ret = ERROR;
	else if ((count_loops == 3 || count_loops == 5) && vct_apply(color,
				IS_WHITESPACEDIGIT) == FALSE)
		ret = ERROR;
	if (count_num != NB_COLOR && count_loops > 5)
		ret = ERROR; 
	count_loops++;
	return (ret);
}

int	have_all_info(t_state_machine *machine)
{
	return (machine->information & BT_RESOLUTION &&
			machine->information & BT_COLOR_F &&
			machine->information & BT_COLOR_C && machine->information & BT_NO
			&& machine->information & BT_SO && machine->information & BT_WE
			&& machine->information & BT_EA && machine->information & BT_SPR);
}

int	have_all_color(t_state_machine *machine)
{
	return (machine->information & BT_COLOR_F &&
				machine->information & BT_COLOR_C);
}
