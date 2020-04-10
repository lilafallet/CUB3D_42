/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/10 15:32:29 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

static int	parser_resolution_text_spr(t_vector *vct, t_state_machine *machine)
{
	size_t	i;
	int		ret;
	t_vector	*resol;
	int			count_num;

	i = 0;
	ret = FALSE;
	count_num = 0;
	resol = vct_splitchr(vct, 'R');	
	vct_del(&resol);
	ft_printf("PARSER_RESOLUTION\n"); //
	if (vct_apply(resol, IS_WHITESPACE) == FALSE)
	{
		vct_del(&resol);
		return (FAILURE);
	}
	while ((resol = vct_split(vct, " \t", ALL_SEP)) != NULL)
	{
		if (vct_apply(resol, IS_DIGIT) == TRUE)
		{
			machine->information |= BT_RESOLUTION;
			machine->info.str_resolution[count_num] = vct_strdup(resol);
			count_num++;
		}
		else if ((vct_apply(resol, IS_WHITESPACE) == FALSE) &&
				(vct_apply(resol, IS_DIGIT) == FALSE))
		{
			machine->information |= ERROR_RESOLUTION;
			vct_del(&resol);
			return (FAILURE);
		}
		vct_del(&resol);
	}
	machine->state = TEXTURE;
	vct_del(&resol);
	ft_printf("PARSER_RESOLUTION IS TRUE\n"); //
	return (TRUE);
	/*while (str[i] != '\0')
	{
		if (str[i] == CHAR_RESOLUTION)
		{
			printf("HELLO 1\n"); //
			ret = hub_recup_texture_resolution(str, i, machine, RESOLUTION);
			printf("ret = %d\n", ret); //
			if (ret == FAILURE)
				machine->information |= ERROR_RESOLUTION;
			if (ret == TRUE)
				machine->information |= BT_RESOLUTION;
			return (ret);
		}
		else if (str[i] == CHAR_TEXTURE_SPR)
		{
			printf("HELLO 2\n"); /8 /
			ret = hub_recup_texture_resolution(str, i, machine, SPRITE_TEXTURE);
			if (ret == TRUE)
				machine->information |= BT_SPR;
			return (ret);
		}
		if (str[i] != SPACE && str[i] != TAB)
		{
			printf("HELLO 3\n"); //
			machine->information |= ERROR_RESOLUTION;
			return (FAILURE);
		}
			printf("HELLO 4\n"); //
		i++;
	}*/
}

static int	parser_texture(t_vector *vct, t_state_machine *machine)
{
	size_t	i;
	int		first_index;
	int		ret;

	i = 0;
	ret = FALSE;
	ft_printf("PARSER_TEXTURE\n"); //
	/*while (str[i] != '\0')
	{
		if (str[i] == SPACE || str[i] == TAB)
			i++;
		if ((first_index = is_texture(str[i])) != FAILURE)
		{
			ret = process_texture(first_index, str, i, machine);
			return (ret);
		}
		i++;
	}*/
	machine->state = COLOR;
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
	static t_function	function[5] = {parser_resolution_text_spr,
										parser_texture,
										parser_resolution_text_spr,
										parser_color, parser_map};
	static int	nb_line = 1; //
	int			ret;
	int			i;

	ft_printf("FIRST PARSER\n"); //
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
		ft_printf("RENTRE DANS LA BOUCLE\n"); //	
		ret = function[machine->state](line, machine);
		if (ret == FAILURE)
			return (FAILURE);
		if (ret == FALSE)
			i++;
		else
			break ;
	}
	nb_line++; /*debug*/
	return (ret);
}
