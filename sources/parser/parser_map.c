/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/17 15:19:13 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	what_information_map(t_vector *vct, size_t clen_map, t_state_machine *machine)
{
	char	*tab_other_map_str[4] = {"NO", "SO", "WE", "EA"};
	char	tab_other_map_c[4] = {"S", "R", "F", "C"};
	size_t	tab_len[9];
	size_t	i;
	size_t	index;

	i = 0;	
	while (i < 4)
	{
		tab_len[i] = vct_strlen(vct, tab_other_map_str[i]);
		i++;
	}
	index = 0;
	while (i < 8)
	{
		tab_len[i] = vct_clen(vct, tab_other_map_c[index]);
		i++;
		index++;
	}
	tab_len[8] = clen_map;
	index = ft_bubblesort_minindex(tab_len, 9);
	if (tab_len[0] == clen_map && tab_len[1] == clen_map
			&& tab_len[2] == clen_map && tab_len[3] == clen_map 
			&& tab_len[4] == clen_map && tab_len[5] == clen_map
			&& tab_len[6] == clen_map && tab_len[7] == clen_map)
		return (TRUE);
	if (index == 0 || index == 1 || index == 2 || index == 3 || index == 4)
		machine->state = TEXTURE;
	if (index == 5)
		machine->state = RESOLUTION;
	if (index == 6 || index == 7)
		machine->state = COLOR;
	return (NEXT);
}
