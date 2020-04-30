/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 22:54:49 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	recup_digit_color(t_vector *split, t_state_machine *map,
								unsigned long flag, uint8_t i)
{
	int			nb;

	if (vct_apply(split, IS_DIGIT) == FALSE)
		map->information |= ERROR_COLOR_NOT_NUMBER;
	else
	{
		if ((nb = vct_apply(split, TO_ATOI)) > 255 || vct_getlen(split) > 3)
			map->information |= ERROR_COLOR_WRONG_TYPE_NUMBER;
		else if (flag == BT_COLOR_F)
			map->info.tab_color_f[i / 2] = nb;
		else
			map->info.tab_color_c[i / 2] = nb;
	}
}

static void	get_color(t_vector *vct, t_state_machine *map,
						unsigned long flag)
{
	t_vector	*split;
	uint8_t		i;
	size_t		count_num;

	i = 0;
	count_num = 0;
	vct_split(NULL, NULL, INIT);
	while ((split = vct_split(vct, ",", EACH_SEP))
			&& (map->information & IS_ERROR) == FALSE)
	{
		if (i % 2 == 0)
		{
			count_num++;
			recup_digit_color(split, map, flag, i);
		}
		else if (i == 5 || vct_getfirstchar(split) != ',')
			map->information |= ERROR_COLOR_NUMBER_COLOR_ARGUMENTS;\
		vct_del(&split);
		i++;
	}
	if (count_num != 3 && (map->information & IS_ERROR) == FALSE)
		map->information |= ERROR_COLOR_NUMBER_COLOR_ARGUMENTS;
	vct_del(&split);
}

int			init_map_color(uint8_t count, t_state_machine *map,
								t_vector *cpy)
{
	int			ret;

	ret = SUCCESS;
	if (count == 0 && (map->information & BT_COLOR_F) == FALSE)
		map->information |= BT_COLOR_F;
	else if (count == 1 && (map->information & BT_COLOR_C) == FALSE)
		map->information |= BT_COLOR_C;
	else
		map->information |= ERROR_COLOR_ALREADY;
	if ((map->information & IS_ERROR) == FALSE)
	{
		get_color(cpy, map, count == 0 ? BT_COLOR_F : BT_COLOR_C);
		vct_del(&cpy);
		return (FAILURE);
	}
	vct_del(&cpy);
	return (ret);
}

int			true_or_false(t_vector *split, t_vector *vct,
							t_state_machine *map, uint8_t count)
{
	t_vector	*cpy;
	int			ret;
	t_vector	*new_split;

	ret = SUCCESS;
	cpy = vct_dup(split);
	if ((new_split = vct_split(vct, " \t", NO_SEP)) != NULL)
		map->information |= ERROR_COLOR_NUMBER_ARGUMENTS;
	if (init_map_color(count, map, cpy) == FAILURE)
		ret = FAILURE;
	vct_del(&new_split);
	return (ret);
}

void		is_color(uint8_t *count, t_vector *split, t_state_machine *map,
						char *tab_color[NB_INDIC_COLOR])
{
	while (*count < NB_INDIC_COLOR
			&& ft_strequ(vct_getstr(split), tab_color[*count]) == FALSE)
		*count = *count + 1;
	if (*count == NB_INDIC_COLOR)
		map->state = MAP;
}
