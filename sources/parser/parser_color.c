/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 10:36:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/22 18:11:29 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

int	what_information_color(t_vector *vct, size_t clen, t_state_machine *machine,
							int ret_before)
{
	char *tab_other_resolution[4] = {"R", "NO", "SO", "WE"};
	size_t	tab_len[5];
	size_t	i;
	size_t	index;
	int		ret;

	i = 0;
	ret = 0;
	while (i < 4)
	{
		tab_len[i] = vct_strlen(vct, tab_other_resolution[i]);
		i++;
	}
	tab_len[4] = clen;
	index = ft_bubblesort_minindex(tab_len, 5);
	if (index == 0)
	{
		machine->state = RESOLUTION;
		ret = NEXT;
	}
	if (index == 1 || index == 2 || index == 3)
	{
		machine->state = TEXTURE;
		ret = NEXT;
	}
	if (tab_len[0] == vct_getlen(vct) && tab_len[1] == vct_getlen(vct)
			&& tab_len[2] == vct_getlen(vct) && tab_len[3] == vct_getlen(vct)
			&& ret_before == TRUE)
		ret = TRUE;
	if (tab_len[0] == vct_getlen(vct) && tab_len[1] == vct_getlen(vct)
			&& tab_len[2] == vct_getlen(vct) && tab_len[3] == vct_getlen(vct)\
			&& ret_before == NEXT_OTHERCHAR)
	{
		machine->state = MAP;
		ret = NEXT;
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

static int	verif_before(t_vector *vct, size_t clen, t_state_machine *machine)
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

static int	error_or_true(t_vector *color, size_t count_loops, size_t count_num)
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

static int	recuperation_color(t_vector *color, char type_color,
								t_state_machine *machine)
{
	int	ret;
	int	num;
	static size_t	index = 0;
	
	ret = TRUE;
	num = ft_atoi(vct_getstr(color));
	if (num < 0 || num > 255)
		ret = ERROR;
	if (type_color == 'F')
	{
		machine->info.tab_color_f[index] = num;
		printf("RECUPERATION_COLOR -> machine->info.tab_color_f[%zu] = %d\n",
				index, machine->info.tab_color_f[index]); //
		ret = TRUE;
		index++;
	}
	else
	{
		machine->info.tab_color_c[index] = num;
		printf("RECUPERATION_COLOR -> machine->info.tab_color_f[%zu] = %d\n",
				index, machine->info.tab_color_c[index]); //
		ret = TRUE;
		index++;
	}	
	if (index == NB_COLOR && ret != ERROR)
	{
		if (type_color == 'F')
			machine->information |= BT_COLOR_F;	
		else
			machine->information |= BT_COLOR_C;	
		if (machine->information & BT_COLOR_F &&
				machine->information & BT_COLOR_C)
			machine->state = MAP;
		index = 0;
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

static int	process_split_color(t_vector *cpy_vct, char type_color,
									t_state_machine *machine)
{
	int	ret;
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
			ret = recuperation_color(color, type_color, machine);
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
static int	split_color(t_vector *vct, char *str, char type_color,
							t_state_machine *machine)
{
	int	ret;
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

int	pre_split_color(t_vector *vct, char *str, t_state_machine *machine)
{
	size_t	clen;
	int		ret;
	char	*str_clen;
	char	type_color;

	ret = TRUE;
	str_clen = NULL;
	clen = vct_clen(vct, str[0]);
	type_color = vct_getcharat(vct, clen);
	ret = verif_before(vct, clen, machine);
	if (ret == TRUE)
	{
		str_clen = vct_getstr(vct);
		str_clen = ft_strdup(str_clen + clen + 1);
		ret = split_color(vct, str_clen, type_color, machine);
	}
	free(str_clen);
	return (ret);
}
