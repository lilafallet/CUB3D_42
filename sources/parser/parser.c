/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 22:54:35 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parser_resolution(t_vector *vct, t_state_machine *map)
{
	t_vector	*split;
	uint8_t		i;

	i = 0;
	vct_split(NULL, NULL, INIT);
	while ((split = vct_split(vct, " \t", NO_SEP))
			&& (map->information & IS_ERROR) == FALSE
			&& map->state == RESOLUTION)
	{
		if (i == 0)
			is_indic_resolution(split, map);
		else if (i == 3)
			map->information |= ERROR_RESOLUTION_NUMBER_ARGUMENTS;
		else
			is_number_resolution(split, map, i);
		vct_del(&split);
		i++;
	}
	vct_del(&split);
	if (map->state == RESOLUTION)
		return (SUCCESS);
	return (FAILURE);
}

static int	parser_texture(t_vector *vct, t_state_machine *map)
{
	char		*tab_texture[NB_TEXTURE] = {"NO", "SO", "WE", "EA", "S"};
	t_vector	*split;
	uint8_t		i;
	uint8_t		count;

	i = 0;
	count = 0;
	while ((split = vct_split(vct, " \t", NO_SEP))
			&& (map->information & IS_ERROR) == FALSE
			&& map->state == TEXTURE)
	{
		if (i == 0)
			is_texture(&count, split, map, tab_texture);
		else if (i == 2)
			map->information |= ERROR_TEXTURE_NUMBER_ARGUMENTS;
		else
			recuperation_texture(map, count, split);
		i++;
		vct_del(&split);
	}
	vct_del(&split);
	if (map->state == TEXTURE)
		map->state = RESOLUTION;
	return (map->state == RESOLUTION ? SUCCESS : FAILURE);
}

static int	parser_color(t_vector *vct, t_state_machine *map)
{
	char		*tab_color[NB_INDIC_COLOR] = {"F", "C"};
	uint8_t		i;
	uint8_t		count;
	t_vector	*split;

	i = 0;
	count = 0;
	while ((split = vct_split(vct, " \t", NO_SEP)) && (map->information
				& IS_ERROR) == FALSE && map->state == COLOR)
	{
		if (i == 0)
			is_color(&count, split, map, tab_color);
		else
		{
			if (true_or_false(split, vct, map, count) == FAILURE)
				break ;
		}
		vct_del(&split);
		i++;
	}
	if (map->state == COLOR)
		map->state = RESOLUTION;
	vct_del(&split);
	return (map->state == RESOLUTION ? SUCCESS : FAILURE);
}

static int	parser_map(t_vector *vct, t_state_machine *map)
{
	int				ret;
	t_vector		*cpy_vct;

	ret = TRUE;
	if ((map->information & ALL_INFO) != ALL_INFO)
		ret = ERROR;
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	if (ret != ERROR)
		ret = is_map(cpy_vct);
	if (ret != ERROR)
		ret = recuperation_map(cpy_vct, map);
	if (ret == ERROR)
	{
		if (map->info.tab_map == NULL)
			printf_errors(ERR_GLOBAL, map->info.nb_line);
		map->information |= (map->info.tab_map == NULL ? IS_ERROR :
									ERROR_MAP_NOT_VALID);
		vct_del(&cpy_vct);
		return (FAILURE);
	}
	vct_del(&cpy_vct);
	return (SUCCESS);
}

int			first_parser(t_state_machine *map, int fd)
{
	static t_function	function[NB_INFO] = {parser_resolution, parser_texture,
										parser_color, parser_map};
	ssize_t				ret;
	t_vector			*line;

	line = vct_new();
	ret = 0;
	while ((map->information & IS_ERROR) == FALSE
			&& (ret = vct_readline(line, fd)) > 0)
	{
		map->info.nb_line++;
		if (line->len == 0 && map->state != MAP)
			continue ;
		vct_split(NULL, NULL, INIT);
		while ((map->information & IS_ERROR) == FALSE
			&& function[map->state](line, map) == FAILURE)
			vct_split(NULL, NULL, INIT);
	}
	vct_del(&line);
	if (map->information & IS_ERROR || ret == FAILURE)
	{
		printf_errors(map->information, map->info.nb_line);
		return (FAILURE);
	}
	return (SUCCESS);
}
