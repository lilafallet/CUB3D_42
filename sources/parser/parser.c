/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/22 14:32:21 by lfallet          ###   ########.fr       */
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
	int			index;
	t_vector	*texture;

	ret = TRUE;
	if (machine->information & BT_NO && machine->information & BT_SO &&
		machine->information & BT_WE && machine->information & BT_EA &&
		machine->information & BT_SPR)
	{
		machine->information |= ERROR_TEXTURE;
		return (ERROR);
	}	
	texture = vct_new();
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	if (ret != ERROR)
		ret = is_texture(cpy_vct, tab_texture, machine);
	index = ret;
	if (ret == NEXT_OTHERCHAR)
	{
		what_information_texture(cpy_vct, vct_getlen(cpy_vct), machine, ret);
		vct_del(&cpy_vct);
		vct_del(&texture);
		return (NEXT);
	}
	if (ret >= NO && ret <= S)
		ret = pre_process_split(texture, cpy_vct, tab_texture[ret]);
	else
		ret = NEXT;
	ret = init_machine_texture(ret, machine, index, cpy_vct);
	ft_printf("machine->information.str_texture[%d] = %s\n", index,
				machine->info.str_texture[index]); //	
	if (machine->information & BT_RESOLUTION &&
			machine->information & BT_COLOR_F &&
			machine->information & BT_COLOR_C && machine->information & BT_NO
			&& machine->information & BT_SO && machine->information & BT_WE
			&& machine->information & BT_EA && machine->information & BT_SPR)
	{
		ret = TRUE;
		machine->state = MAP;
	}
	vct_del(&cpy_vct);
	vct_del(&texture);
	return (ret);
}

static int	parser_color(t_vector *vct, t_state_machine *machine)
{
	int			ret;
	t_vector	*cpy_vct;
	char		*tab_color[NB_INDIC_COLOR] = {"F", "C"};
	int			index;

	if (machine->information & BT_COLOR_F && machine->information & BT_COLOR_C)
	{
		machine->information |= ERROR_COLOR;
		ret = ERROR;
	}
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	ret = is_color(cpy_vct, tab_color);
	index = ret;
	if (ret == COLOR_C || ret == COLOR_F)
		ret = TRUE;
	else
		ret = NEXT;
	if (ret == TRUE)
		ret = pre_split_color(cpy_vct, tab_color[index], machine); 
	if (ret == NEXT)
	{
		ret = what_information_color(vct, vct_getlen(vct), machine,
										NEXT_OTHERCHAR);
	}
	if (ret == ERROR)
		machine->information |= ERROR_COLOR;
	if (ret == TRUE && (((machine->information & BT_COLOR_F) == FALSE ||
			(machine->information & BT_COLOR_C) == FALSE)))
		ret = ERROR;
	vct_del(&cpy_vct);
	return (ret);	
}

static int	parser_map(t_vector *vct, t_state_machine *machine)
{
	int	ret;
	t_vector	*cpy_vct;
	static size_t	count_loops_function = 0;

	ret = TRUE;
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	if (count_loops_function == 0)
		ret = what_information_map(cpy_vct, vct_getlen(vct), machine);
	if (ret == NEXT)
	{	
		count_loops_function++;
		return (NEXT);
	}
	ret = is_map(cpy_vct);
	if (ret == ERROR)
	{
		machine->information |= ERROR_MAP;
		vct_del(&cpy_vct);
		return (ERROR);
	}
	ret = recuperation_map(cpy_vct, machine);
	if (ret == ERROR)
		machine->information |= ERROR_MAP;
	vct_del(&cpy_vct);
	return (ret);
}

int			first_parser(t_state_machine *machine, t_vector *line)
{
	static t_function	function[4] = {parser_resolution, parser_texture,
										parser_color, parser_map};
	int					ret;
	int					i;

	i = 0;
	ret = 0;
	if (line->len == 0)
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
