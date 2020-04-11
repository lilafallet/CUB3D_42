/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/11 17:11:58 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

static int	parser_resolution(t_vector *vct, t_state_machine *machine)
{
	t_vector	*resol;
	int			ret;
	t_vector	*cpy_vct;

	ft_printf("PARSER_RESOLUTION\n\n"); //
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	resol = NULL;
	ret = TRUE;
	ret = is_resolution(resol, cpy_vct);
	if (ret != ERROR && ret != NEXT)
		ret = resolution_details(resol, machine->info.str_resolution, cpy_vct);
	if (ret & NEXT)
		ret = is_true_and_next(machine, ret);
	if (ret & ERROR)
		machine->information |= ERROR_RESOLUTION;
	vct_del(&cpy_vct);
	return (ret);
}

static int	parser_texture(t_vector *vct, t_state_machine *machine)
{
	int			ret;
	t_vector	*text;
	t_vector	*cpy_vct;

	ft_printf("PARSER_TEXTURE\n"); //
	ft_printf("text->str = %s\n", vct_getstr(vct)); //
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	text = NULL;
	ret = is_texture(text, cpy_vct);
	return (ret);
}

static int			parser_color(t_vector *vct, t_state_machine *machine)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = FALSE;
	ft_printf("PARSER_COLOR\n"); //
	/*while (str[i] != '\0')
	{
		if (str[i] == CHAR_F_COLOR)
		{
			ret = hub_recup_color(str, i, machine, str[i], COLOR_F);
			if (ret == FAILURE)
				machine->information |= ERROR_COLOR;
			return (ret);
		}
		else if (str[i] == CHAR_C_COLOR)
		{
			ret = hub_recup_color(str, i, machine, str[i], COLOR_C);
			if (ret == FAILURE)
				machine->information |= ERROR_COLOR;
			return (ret);
		}
		i++;
	}*/
	machine->state = MAP;
	return (ret);
}

static int			parser_map(t_vector *vct, t_state_machine *machine)
{
	int				ret;
	static size_t	index = 0;
	int				position;

	ret = TRUE;
	ft_printf("PARSER_MAP\n"); //
	/*machine->info.str_map[index] = ft_memdup(str, ft_strlen(str));
	printf("machine->info.str_map[%lu] = %s\n", index, machine->info.str_map[index]); //
	position = what_position(machine->info.str_map[index],
								machine->info.str_position);
	printf("position = %d\n\n", position); //
	if (position != FAILURE)
		machine->information |= (unsigned long)((1 << position) << 20);
	index++;*/
	return (ret);
}

int			first_parser(t_state_machine *machine, t_vector *line)
{
	static t_function	function[4] = {parser_resolution, parser_texture,
										parser_color, parser_map};
	static int	nb_line = 1; //
	int			ret;
	int			i;

	ft_printf("TEST LINE %d: %s\n\n", nb_line, line->str); //
	i = 0;
	ret = 0;
	if (line->len == 0)
	{
		ft_printf("LEN LINE = 0\n"); //
		nb_line++;
		//what_state(machine);
		return (LEN_ZERO);
	}
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
	nb_line++; /*debug*/
	return (ret);
}
