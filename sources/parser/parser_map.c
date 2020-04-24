/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/24 21:19:04 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		verif_before(t_vector *vct, size_t clen)
{
	char	*str;
	size_t	i;
	int		ret;

	str = vct_getstr(vct);
	i = 0;
	ret = TRUE;
	while (i < clen)
	{
		if (str[i] != SPACE && str[i] != TAB)
			ret = ERROR;
		i++;
	}
	return (ret);
}

int				is_map(t_vector *vct)
{
	int			ret;
	t_vector	*cpy_vct;
	size_t		clen;

	ret = TRUE;
	clen = 0;
	cpy_vct = vct_dup(vct);
	clen = vct_clen(cpy_vct, CHAR_WALL);
	if (clen != 0)
		ret = verif_before(cpy_vct, clen);
	vct_del(&cpy_vct);
	return (ret);
}

static size_t	fill_tab_str(size_t tab_len[NB_DIFF_MAP_STR], t_vector *vct,
								char *tab_other_map_str[NB_DIFF_MAP_STR])
{
	size_t	i;

	i = 0;
	while (i < NB_DIFF_MAP_STR)
	{
		tab_len[i] = vct_strlen(vct, tab_other_map_str[i]);
		i++;
	}
	return (i);
}

static void		fill_tab_c(size_t tab_len[DIFF_LEN_MAP], size_t i,
						char tab_other_map_c[NB_DIFF_MAP_C], t_vector *vct)
{
	size_t	index;

	index = 0;
	while (i < DIFF_LEN_MAP - 1)
	{
		tab_len[i] = vct_clen(vct, tab_other_map_c[index]);
		i++;
		index++;
	}
}

int				what_information_map(t_vector *vct, size_t clen_map,
							t_state_machine *machine)
{
	char	*tab_other_map_str[NB_DIFF_MAP_STR] = {"NO", "SO", "WE", "EA"};
	char	tab_other_map_c[NB_DIFF_MAP_C] = {'S', 'R', 'F', 'C'};
	size_t	tab_len[DIFF_LEN_MAP];
	size_t	index;
	size_t	i;

	index = 0;
	i = fill_tab_str(tab_len, vct, tab_other_map_str);
	fill_tab_c(tab_len, i, tab_other_map_c, vct);
	tab_len[DIFF_LEN_MAP - 1] = clen_map;
	index = ft_bubblesort_minindex(tab_len, DIFF_LEN_MAP);
	if (tab_len[IND_NO_MAP] == clen_map && tab_len[IND_SO_MAP] == clen_map
			&& tab_len[IND_WE_MAP] == clen_map
			&& tab_len[IND_EA_MAP] == clen_map && tab_len[IND_S_MAP] == clen_map
			&& tab_len[IND_R_MAP] == clen_map && tab_len[IND_F_MAP] == clen_map
			&& tab_len[IND_C_MAP] == clen_map)
		return (TRUE);
	if (index == IND_NO_MAP || index == IND_SO_MAP || index == IND_WE_MAP ||
			index == IND_EA_MAP || index == IND_S_MAP)
		machine->state = TEXTURE;
	if (index == IND_R_MAP)
		machine->state = RESOLUTION;
	if (index == IND_F_MAP || index == IND_C_MAP)
		machine->state = COLOR;
	return (NEXT);
}
