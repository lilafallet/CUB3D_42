/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/11 12:42:28 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parser_resolution(t_vector *vct, t_map *map,
								t_state_machine *machine)
{
	t_vector	*split;
	uint8_t		i;

	i = 0;
	vct_split(NULL, NULL, INIT);
	while ((split = vct_split(vct, " \t", NO_SEP))
			&& (machine->info & IS_ERROR) == FALSE
			&& machine->state == RESOLUTION)
	{
		if (i == 0)
			is_indic_resolution(split, machine);
		else if (i == 3)
			machine->info |= ERROR_RESOLUTION_NUMBER_ARGUMENTS;
		else
			is_number_resolution(split, machine, i, map);
		vct_del(&split);
		i++;
	}
	vct_del(&split);
	if (machine->state == RESOLUTION)
		return (SUCCESS);
	return (FAILURE);
}

static int	parser_texture(t_vector *vct, t_map *map, t_state_machine *machine)
{
	const char		*tab_texture[NB_TEXTURE] = {"NO", "SO", "WE", "EA", "S"};
	t_vector	*split;
	uint8_t		i;
	uint8_t		count;

	i = 0;
	count = 0;
	while ((split = vct_split(vct, " \t", NO_SEP))
			&& (machine->info & IS_ERROR) == FALSE
			&& machine->state == TEXTURE)
	{
		if (i == 0)
			is_texture(&count, split, machine, tab_texture);
		else if (i == 2)
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
	const char		*tab_color[NB_INDIC_COLOR] = {"F", "C"};
	uint8_t		i;
	uint8_t		count;
	t_vector	*split;

	i = 0;
	count = 0;
	while ((split = vct_split(vct, " \t", NO_SEP)) && (machine->info
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
			printf_errors(ERR_GLOBAL, map->utils.nb_line);
		machine->info |= (map->recup.tab_map == NULL ? IS_ERROR :
									ERROR_MAP_NOT_VALID);
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

	line = vct_new();
	ret = 0;
	while ((machine->info & IS_ERROR) == FALSE
			&& (ret = vct_readline(line, fd)) > 0)
	{
		map->utils.nb_line++;
		if (line->len == 0 && machine->state != MAP)
			continue ;
		vct_split(NULL, NULL, INIT);
		while ((machine->info & IS_ERROR) == FALSE
			&& function[machine->state](line, map, machine) == FAILURE)
			vct_split(NULL, NULL, INIT);
	}
	vct_del(&line);
	if (machine->info & IS_ERROR || ret == FAILURE)
	{
		printf_errors(machine->info, map->utils.nb_line);
		return (FAILURE);
	}
	return (SUCCESS);
}
