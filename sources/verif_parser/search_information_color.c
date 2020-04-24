/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_information_color.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:16:52 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/24 17:22:20 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_tab_len(size_t tab_len[DIFF_LEN_COLOR], t_vector *vct,
							char *tab_other_resolution[NB_DIFF_COLOR])
{
	size_t	i;

	i = 0;
	while (i < NB_DIFF_COLOR)
	{
		tab_len[i] = vct_strlen(vct, tab_other_resolution[i]);
		i++;
	}
}

int	what_information_color(t_vector *vct, size_t clen, t_state_machine *machine,
							int ret_before)
{
	char *tab_other_resolution[NB_DIFF_COLOR] = {"R", "NO", "SO", "WE"};
	size_t	tab_len[DIFF_LEN_COLOR];
	size_t	index;
	int		ret;

	fill_tab_len(tab_len, vct, tab_other_resolution);
	tab_len[NB_DIFF_COLOR] = clen;
	index = ft_bubblesort_minindex(tab_len, DIFF_LEN_COLOR);
	ret = what_state_color(index, machine);
	if (tab_len[IND_R_COLOR] == vct_getlen(vct)
			&& tab_len[IND_NO_COLOR] == vct_getlen(vct)
			&& tab_len[IND_SO_COLOR] == vct_getlen(vct)
			&& tab_len[IND_WE_COLOR] == vct_getlen(vct) && ret_before == TRUE)
		ret = TRUE;
	if (tab_len[IND_R_COLOR] == vct_getlen(vct)
			&& tab_len[IND_NO_COLOR] == vct_getlen(vct)
			&& tab_len[IND_SO_COLOR] == vct_getlen(vct)
			&& tab_len[IND_WE_COLOR] == vct_getlen(vct)
			&& ret_before == NEXT_OTHERCHAR)
	{
		machine->state = MAP;
		ret = NEXT;
	}
	return (ret); 
}

int	what_state_color(size_t index, t_state_machine *machine)
{
	int	ret;

	ret = TRUE;
	if (index == IND_R_COLOR)
	{
		machine->state = RESOLUTION;
		ret = NEXT;
	}
	if (index == IND_NO_COLOR || index == IND_SO_COLOR || index == IND_WE_COLOR)
	{
		machine->state = TEXTURE;
		ret = NEXT;
	}
	return (ret);
}
