/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_information_resolution.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:45:36 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/24 21:37:05 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	what_information_resolution(t_vector *vct, t_state_machine *machine)
{
	char	*tab_other_resolution[NB_DIFF_RESOL] = {"NO", "SO", "WE", "F", "C"};
	size_t	tab_len[DIFF_LEN_RESOL];
	size_t	index;
	int		ret;

	ret = 0;
	fill_tab_len_resolution(tab_len, vct, tab_other_resolution);
	tab_len[NB_DIFF_RESOL] = vct_strlen(vct, STR_RESOLUTION);
	index = ft_bubblesort_minindex(tab_len, NB_DIFF_RESOL);
	if (index == IND_NO_RESOL || index == IND_SO_RESOL || index == IND_WE_RESOL)
	{
		machine->state = TEXTURE;
		ret = NEXT;
	}
	if (index == IND_F_RESOL || index == IND_C_RESOL)
	{
		machine->state = COLOR;
		ret = NEXT;
	}
	if (tab_len[IND_NO_RESOL] == vct_getlen(vct)
		&& tab_len[IND_SO_RESOL] == vct_getlen(vct) && tab_len[IND_WE_RESOL]
		== vct_getlen(vct) && tab_len[IND_F_RESOL] == vct_getlen(vct)
		&& tab_len[IND_C_RESOL] == vct_getlen(vct))
		ret = TRUE;
	return (ret);
}

int	is_resolution(t_vector *resol, t_vector *vct, t_state_machine *machine)
{
	int	ret;

	ret = TRUE;
	if (vct_chr(vct, CHAR_RESOLUTION) == FAILURE)
		return (NEXT);
	ret = what_information_resolution(vct, machine);
	if (ret == NEXT)
		return (NEXT);
	resol = vct_splitchr(vct, CHAR_RESOLUTION);
	if ((vct_getfirstchar(vct) != SPACE) && (vct_getfirstchar(vct) != TAB))
	{
		vct_del(&resol);
		return (ERROR);
	}
	if (vct_apply(resol, IS_WHITESPACE) == FALSE)
		ret = not_resolution(resol);
	vct_del(&resol);
	return (ret);
}

int	is_invalid_char(t_vector *resol)
{
	return ((vct_apply(resol, IS_WHITESPACE) == FALSE) &&
				(vct_apply(resol, IS_DIGIT) == FALSE));
}

int	count_num(char **str_resolution, t_vector *resol)
{
	int			ret;
	static int	count_num = 0;

	ret = NEXT | TRUE;
	if (count_num <= AXE_Y)
	{
		str_resolution[count_num] = vct_strdup(resol);
		if (str_resolution[AXE_X] != NULL && str_resolution[AXE_Y] != NULL)
		{
			ft_printf("RECUPERATION_RESOLUTION -> machine->info.str_resolution[AXE_X] = %s\n", str_resolution[AXE_X]); //
			ft_printf("RECUPERATION_RESOLUTION -> machine->info.str_resolution[AXE_Y] = %s\n", str_resolution[AXE_Y]); //
		}
		count_num++;
	}
	else
		ret = ERROR;
	return (ret);
}

int	not_resolution(t_vector *vct)
{
	char	*str;
	size_t	i;
	int		ret;

	ret = ERROR;
	str = vct_getstr(vct);
	i = 0;
	if (ft_strchr(STRING_CHECK_R, str[FIRST_CHAR]) != NULL)
		ret = NEXT;
	if (ft_strequ(str, STR_TEXTURE_NO) == TRUE ||
			ft_strequ(str, STR_TEXTURE_SO) == TRUE ||
			ft_strequ(str, STR_TEXTURE_WE) == TRUE ||
			ft_strequ(str, STR_TEXTURE_EA) == TRUE)
		ret = NEXT;
	return (ret);
}
