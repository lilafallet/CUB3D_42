/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/27 11:47:44 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t			fill_line(t_state_machine *machine, enum e_map **cpy_tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < machine->info.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) *
				(machine->info.max_index));
		ft_memset(cpy_tab[i], STOP, machine->info.max_index);
		j = 0;
		while (j < machine->info.max_index
				&& machine->info.tab_map[i][j] != STOP)
		{
			cpy_tab[i][j] = machine->info.tab_map[i][j];
			j++;
		}
		while (j < machine->info.max_index)
			cpy_tab[i][j++] = STOP;
		free(machine->info.tab_map[i]);
		i++;
	}
	return (i);
}

int				realloc_tab(t_state_machine *machine, size_t count_line,
		size_t old_index, size_t new_index)
{
	enum e_map	**cpy_tab;
	size_t		i;

	if (old_index == 0 || new_index > old_index)
		machine->info.max_index = new_index;
	cpy_tab = (enum e_map **)malloc(sizeof(enum e_map *) * (count_line));
	ft_bzero(cpy_tab, machine->info.count_line);
	i = fill_line(machine, cpy_tab);
	if (count_line != machine->info.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) *
				machine->info.max_index);
		ft_memset(cpy_tab[i], STOP, machine->info.max_index);
	}
	free(machine->info.tab_map);
	machine->info.tab_map = cpy_tab;
	return (SUCCESS);
}

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
