/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 10:36:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/24 21:31:18 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

int			send_to_function_color(t_vector *cpy_vct,
									char *tab_color[NB_INDIC_COLOR],
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

int			pre_split_color(t_vector *vct, char *str, t_state_machine *machine)
{
	size_t	clen;
	int		ret;
	char	*str_clen;
	char	type_color;

	ret = TRUE;
	str_clen = NULL;
	clen = vct_clen(vct, str[0]);
	type_color = vct_getcharat(vct, clen);
	ret = verif_before_color(vct, clen, machine);
	if (ret == TRUE)
	{
		str_clen = vct_getstr(vct);
		str_clen = ft_strdup(str_clen + clen + 1);
		ret = split_color(vct, str_clen, type_color, machine);
	}
	free(str_clen);
	return (ret);
}

static int	process_split_color(t_vector *cpy_vct, char type_color,
									t_state_machine *machine)
{
	int			ret;
	t_vector	*color;

	ret = TRUE;
	while ((color = vct_split(cpy_vct, ", \t", ALL_SEP)) != NULL)
	{
		ret = error_or_true(color, machine->info.count_loops,
								machine->info.count_num);
		if (ret == ERROR)
			break ;
		if (vct_apply(color, IS_DIGIT) == TRUE &&
				machine->info.count_loops != 0)
		{
			ret = hub_recuperation_color(color, type_color, machine);
			machine->info.count_num++;
			if (ret == ERROR)
				break ;
		}
		if (vct_chr(color, COMMA) != FAILURE)
			machine->info.count_comma++;
		machine->info.count_loops++;
		vct_del(&color);
	}
	vct_del(&color);
	return (ret);
}

int			split_color(t_vector *vct, char *str, char type_color,
							t_state_machine *machine)
{
	int			ret;
	t_vector	*cpy_vct;

	cpy_vct = vct_new();
	vct_addstr(cpy_vct, str);
	ret = TRUE;
	process_split_color(cpy_vct, type_color, machine);
	if (machine->info.count_comma != NB_COMMA)
		ret = ERROR;
	vct_del(&cpy_vct);
	machine->info.count_loops = 0;
	machine->info.count_num = 0;
	machine->info.count_comma = 0;
	return (ret);
}
