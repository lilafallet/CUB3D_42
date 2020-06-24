/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 19:36:46 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parser_resolution(t_vector *vct, t_map *map,
								t_state_machine *machine)
{
	t_vector	*split;
	uint8_t		i;

	i = 0;
	vct_split(NO_VECTOR, NO_VECTOR, INIT);
	while ((split = vct_split(vct, STRING_SPACE_TAB, NO_SEP))
			&& (machine->info & IS_ERROR) == FALSE
			&& machine->state == RESOLUTION)
	{
		if (i == NB_INDIC_RESOL)
			is_indic_resolution(split, machine);
		else if (i == SUP_MAX_RESOL)
			machine->info |= ERROR_RESOLUTION_NUMBER_ARGUMENTS;
		else
			is_number_resolution(split, machine, i, map);
		vct_del(&split);
		i++;
	}
	vct_del(&split);
	if (map->utils.count_resolution == NOT_ENOUGH
			|| map->utils.count_resolution > TO_MUCH)
		machine->info |= ERROR_RESOLUTION_WRONG_TYPE_NUMBER;
	if (machine->state == RESOLUTION)
		return (SUCCESS);
	return (FAILURE);
}

static int	parser_texture(t_vector *vct, t_map *map, t_state_machine *machine)
{
	const char	*tab_texture[NB_TEXTURE] = {"NO", "SO", "WE", "EA", "S"};
	t_vector	*split;
	uint8_t		i;
	uint8_t		count;

	i = 0;
	count = 0;
	while ((split = vct_split(vct, STRING_SPACE_TAB, NO_SEP))
			&& (machine->info & IS_ERROR) == FALSE
			&& machine->state == TEXTURE)
	{
		if (i == 0)
			is_texture(&count, split, machine, tab_texture);
		else if (i == SUP_MAX_TEXT)
			machine->info |= ERROR_TEXTURE_NUMBER_ARGUMENTS;
		else
			recuperation_texture(machine, count, split, map);
		i++;
		vct_del(&split);
	}
	vct_del(&split);
	if (machine->state == TEXTURE)
		machine->state = RESOLUTION;
	return (machine->state == RESOLUTION ? SUCCESS : FAILURE);
}

static int	parser_color(t_vector *vct, t_map *map, t_state_machine *machine)
{
	const char	*tab_color[NB_INDIC_COLOR] = {"F", "C"};
	uint8_t		i;
	uint8_t		count;
	t_vector	*split;

	i = 0;
	count = 0;
	(void)map;
	while ((split = vct_split(vct, STRING_SPACE_TAB, NO_SEP)) && (machine->info
				& IS_ERROR) == FALSE && machine->state == COLOR)
	{
		if (i == 0)
			is_color(&count, split, machine, tab_color);
		else
		{
			if (true_or_false(split, vct, count, machine) == FAILURE)
				break ;
		}
		vct_del(&split);
		i++;
	}
	if (machine->state == COLOR)
		machine->state = RESOLUTION;
	vct_del(&split);
	return (machine->state == RESOLUTION ? SUCCESS : FAILURE);
}

static int	parser_map(t_vector *vct, t_map *map, t_state_machine *machine)
{
	int				ret;
	t_vector		*cpy_vct;

	ret = TRUE;
	if ((machine->info & ALL_INFO) != ALL_INFO)
		ret = ERROR;
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	if (ret != ERROR)
		ret = is_map(cpy_vct);
	if (ret != ERROR)
		ret = recuperation_map(cpy_vct, map);
	if (ret == ERROR)
	{
		if (map->recup.tab_map == NULL)
			error(map, ERROR_GLOBAL, vct);
		machine->info |= (map->recup.tab_map == NULL ? IS_ERROR :
									ERROR_MAP_LOT_POSITION);
		vct_del(&cpy_vct);
		return (FAILURE);
	}
	vct_del(&cpy_vct);
	return (SUCCESS);
}

int			first_parser(t_map *map, int fd, t_state_machine *machine)
{
	static t_function	function[NB_INFO] = {parser_resolution, parser_texture,
										parser_color, parser_map};
	ssize_t				ret;
	t_vector			*line;
	ssize_t				ret_function;

	line = vct_new();
	ret = 0;
	while ((machine->info & IS_ERROR) == FALSE
			&& (ret = vct_readline(line, fd)) > 0)
	{
		map->utils.nb_line++;
		if (line->len == 0 && machine->state != MAP)
			continue ;
		vct_split(NO_VECTOR, NO_VECTOR, INIT);
		while ((machine->info & IS_ERROR) == FALSE
			&& function[machine->state](line, map, machine) == FAILURE)
			vct_split(NO_VECTOR, NO_VECTOR, INIT);
	}
	map->utils.fd = fd;
	vct_readline(NO_VECTOR, CLEANUP);
	ret_function = gestion_parser(ret, line, map, machine);
	vct_del(&line);
	return (ret_function);
}
