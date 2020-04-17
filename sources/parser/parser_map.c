/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/17 18:03:42 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	verification_map(t_vector *line, t_vector *vct,
								t_state_machine *machine)
{
	int ret;
	t_vector	*map;

	ret = TRUE;
	ft_printf("VERIFICATION_MAP -> vct->str = %s\n", vct_getstr(vct)); //
	while ((map = vct_split(vct, "12NSEW", ALL_SEP)) != NULL)
	{
		ft_printf("VERIFICATION_MAP -> map->str = %s\n", vct_getstr(map)); //
		vct_del(&map);
	}
	return (ret);
}

int	recuperation_map(t_vector *vct, t_state_machine *machine)
{
	int	ret;
	t_vector	*cpy_vct;
	char		*str;
	size_t		clen;

	ret = TRUE;
	cpy_vct = vct_new();
	clen = vct_clen(vct, '1');
	str = vct_getstr(vct);
	str = ft_strdup(str + clen);
	vct_addstr(cpy_vct, str);
	ft_printf("cpy_vct->str = %s\n", vct_getstr(cpy_vct));
	ret = verification_map(vct, cpy_vct, machine);
	vct_del(&cpy_vct);
	return (ret);
}

static int	verif_before(t_vector *vct, size_t clen)
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
	free(str);
	return (ret);
}

int	is_map(t_vector *vct)
{
	int	ret;
	t_vector	*cpy_vct;
	size_t		clen;

	ret = TRUE;
	clen = 0;
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	clen = vct_clen(cpy_vct, '1');
	if (clen != 0)
		ret = verif_before(cpy_vct, clen);
	return (ret);
}

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


