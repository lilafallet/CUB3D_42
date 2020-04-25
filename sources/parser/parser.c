/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/25 16:05:29 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parser_resolution(t_vector *vct, t_state_machine *machine)
{
	t_vector	*resol;
	int			ret;
	t_vector	*cpy_vct;

	ret = TRUE;
	if (machine->information & BT_RESOLUTION)
		ret = ERROR;
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	resol = NULL;
	if (ret != ERROR)
		ret = is_resolution(resol, cpy_vct, machine);
	if (ret != ERROR && ret != NEXT)
		ret = split_resolution(resol, machine->info.str_resolution, cpy_vct);
	if (ret & NEXT)
		ret = init_machine_resolution(machine, ret);
	if (ret & ERROR)
		machine->information |= ERROR_RESOLUTION;
	vct_del(&cpy_vct);
	return (ret);
}

static int	parser_texture(t_vector *vct, t_state_machine *machine)
{
	int			ret;
	t_vector	*cpy_vct;
	char		*tab_texture[NB_TEXTURE] = {"NO", "SO", "WE", "EA", "S"};
	t_vector	*texture;

	ret = TRUE;
	if (have_all_texture(machine) == TRUE)
	{
		machine->information |= ERROR_TEXTURE;
		return (ERROR);
	}
	texture = vct_new();
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	ret = send_to_function_texture(cpy_vct, tab_texture, machine, texture);
	vct_del(&cpy_vct);
	vct_del(&texture);
	return (ret);
}

static int	parser_color(t_vector *vct, t_state_machine *machine)
{
	int			ret;
	t_vector	*cpy_vct;
	char		*tab_color[NB_INDIC_COLOR] = {"F", "C"};

	if (machine->information & BT_COLOR_F && machine->information & BT_COLOR_C)
	{
		machine->information |= ERROR_COLOR;
		ret = ERROR;
	}
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	ret = send_to_function_color(cpy_vct, tab_color, machine, vct);
	vct_del(&cpy_vct);
	return (ret);
}

static int	parser_map(t_vector *vct, t_state_machine *machine)
{
	int				ret;
	t_vector		*cpy_vct;
	static size_t	count_loops_function = 0;

	if ((machine->information & ALL_INFO) != ALL_INFO)
	{
		ft_printf("Miss Informations\n");
		machine->information |= ERROR_MAP; //miss information//
		return (ERROR);
	}
	ret = TRUE;
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	if (count_loops_function == 0)
		ret = what_information_map(cpy_vct, vct_getlen(vct), machine);
	if (ret == NEXT)
		count_loops_function++;
	ret = is_map(cpy_vct);
	if (ret == ERROR && ret != NEXT)
	{
		machine->information |= ERROR_MAP;
		vct_del(&cpy_vct);
		return (ERROR);
	}
	ret = recuperation_map(cpy_vct, machine);
	if (ret == ERROR && ret != NEXT)
		machine->information |= ERROR_MAP;
	vct_del(&cpy_vct);
	return (ret);
}

int			first_parser(t_state_machine *machine, t_vector *line)
{
	static t_function	function[NB_INFO] = {parser_resolution, parser_texture,
										parser_color, parser_map};
	int					ret;
	int					i;

	i = 0;
	ret = 0;
	if (line->len == 0 && machine->state != MAP)
		return (LEN_ZERO);
	while (i < NB_STATE)
	{
		ret = function[machine->state](line, machine);
		if (ret & ERROR)
			return (FAILURE);
		if (ret & NEXT)
			i++;
		else
			break ;
	}
	return (ret);
}
