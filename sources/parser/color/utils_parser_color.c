/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/03 13:07:54 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	recup_digit_color(t_vector *split, unsigned long flag,
								uint8_t i, t_map *map, t_state_machine *machine)
{
	int				nb;

	if (vct_apply(split, IS_DIGIT) == FALSE)
		machine->info |= ERROR_COLOR_NOT_NUMBER;
	else
	{
		if ((nb = vct_apply(split, TO_ATOI)) > 255 || vct_getlen(split) > 3)
			machine->info |= ERROR_COLOR_WRONG_TYPE_NUMBER;
		else if (flag == BT_COLOR_F)
			map->recup.tab_color_f[i / 2] = nb;
		else
			map->recup.tab_color_c[i / 2] = nb;
	}
}

static void	get_color(t_vector *vct, t_state_machine *machine, t_map *map,
						unsigned long flag)
{
	t_vector	*split;
	uint8_t		i;
	size_t		count_num;

	i = 0;
	count_num = 0;
	vct_split(NULL, NULL, INIT);
	while ((split = vct_split(vct, ",", EACH_SEP))
			&& (machine->info & IS_ERROR) == FALSE)
	{
		if (i % 2 == 0)
		{
			count_num++;
			recup_digit_color(split, flag, i, map, machine);
		}
		else if (i == 5 || vct_getfirstchar(split) != ',')
			machine->info |= ERROR_COLOR_NUMBER_COLOR_ARGUMENTS;
		vct_del(&split);
		i++;
	}
	if (count_num != 3 && (machine->info & IS_ERROR) == FALSE)
		machine->info |= ERROR_COLOR_NUMBER_COLOR_ARGUMENTS;
	vct_del(&split);
}

int			init_machine_color(uint8_t count, t_state_machine *machine,
								t_vector *cpy, t_map *map)
{
	int			ret;

	ret = SUCCESS;
	if (count == 0 && (machine->info & BT_COLOR_F) == FALSE)
		machine->info |= BT_COLOR_F;
	else if (count == 1 && (machine->info & BT_COLOR_C) == FALSE)
		machine->info |= BT_COLOR_C;
	else
		machine->info |= ERROR_COLOR_ALREADY;
	if ((machine->info & IS_ERROR) == FALSE)
	{
		get_color(cpy, machine, map, count == 0 ? BT_COLOR_F : BT_COLOR_C);
		vct_del(&cpy);
		return (FAILURE);
	}
	vct_del(&cpy);
	return (ret);
}

int			true_or_false(t_vector *split, t_vector *vct, uint8_t count,
							t_map *map, t_state_machine *machine)
{
	t_vector	*cpy;
	int			ret;
	t_vector	*new_split;

	ret = SUCCESS;
	cpy = vct_dup(split);
	if ((new_split = vct_split(vct, " \t", NO_SEP)) != NULL)
		machine->info |= ERROR_COLOR_NUMBER_ARGUMENTS;
	if (init_machine_color(count, machine, cpy, map) == FAILURE)
		ret = FAILURE;
	vct_del(&new_split);
	return (ret);
}

void		is_color(uint8_t *count, t_vector *split, t_state_machine *machine,
						char *tab_color[NB_INDIC_COLOR])
{
	while (*count < NB_INDIC_COLOR
			&& ft_strequ(vct_getstr(split), tab_color[*count]) == FALSE)
		*count = *count + 1;
	if (*count == NB_INDIC_COLOR)
		machine->state = MAP;
}
