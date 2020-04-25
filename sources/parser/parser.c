/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/25 18:10:41 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parser_resolution(t_vector *vct, t_state_machine *machine)
{
	t_vector	*split;
	uint8_t		i;

	i = 0;
	vct_split(NULL, NULL, INIT);
	while ((split = vct_split(vct, " \t", NO_SEP))
			&& (machine->information & IS_ERROR) == FALSE
			&& machine->state == RESOLUTION)
	{
		if (i == 0)
		{
			if (ft_strequ(vct_getstr(split), "R") == FALSE)
				machine->state = TEXTURE;
			else
			{
				if (machine->information & BT_RESOLUTION)
					machine->information |= ERROR_RESOLUTION;
				else
					machine->information |= BT_RESOLUTION;
			}
		}
		else if (i == 3)
			machine->information |= ERROR_RESOLUTION;
		else
		{
			if (vct_apply(split, IS_DIGIT) == FALSE)
				machine->information |= ERROR_RESOLUTION;
			else
				machine->info.str_resolution[i - 1] = vct_apply(split, TO_ATOI);
		}
		vct_del(&split);
		i++;
	}
	vct_del(&split);
	if (machine->state == RESOLUTION)
		return (SUCCESS);
	return (FAILURE);
}

static int	parser_texture(t_vector *vct, t_state_machine *machine)
{
	char		*tab_texture[NB_TEXTURE] = {"NO", "SO", "WE", "EA", "S"};
	t_vector	*split;
	uint8_t		i;
	uint8_t		count;

	i = 0;
	count = 0;
	while ((split = vct_split(vct, " \t", NO_SEP))
			&& (machine->information & IS_ERROR) == FALSE
			&& machine->state == TEXTURE)
	{
		if (i == 0)
		{
			while (count < NB_TEXTURE
				&& ft_strequ(vct_getstr(split), tab_texture[count]) == FALSE)
				count++;
			if (count == NB_TEXTURE)
				machine->state = COLOR;
		}
		else if (i == 2)
			machine->information |= ERROR_TEXTURE;
		else
		{
			if (machine->info.str_texture[count] != NULL)
				machine->information |= ERROR_TEXTURE;
			else
			{
				machine->info.str_texture[count] = vct_strdup(split);
				machine->information |= (1 << count);
			}
		}
		i++;
		vct_del(&split);
	}
	vct_del(&split);
	if (machine->state == TEXTURE)
	{
		machine->state = RESOLUTION;
		return (SUCCESS);
	}
	return (FAILURE);
}

static void	get_color(t_vector *vct, t_state_machine *machine, unsigned long flag)
{
	t_vector	*split;
	uint8_t		i;
	int			nb;
	
	i = 0;
	vct_split(NULL, NULL, INIT);
	while ((split = vct_split(vct, ",", EACH_SEP))
			&& (machine->information & IS_ERROR) == FALSE)
	{
		if (i % 2 == 0)
		{
			if (vct_apply(split, IS_DIGIT) == FALSE)
				machine->information |= ERROR_COLOR;
			else
			{
				if ((nb = vct_apply(split, TO_ATOI)) > 255)
					machine->information |= ERROR_COLOR;
				else if (flag == BT_COLOR_F)
					machine->info.tab_color_f[i / 2] = nb;	
				else
					machine->info.tab_color_c[i / 2] = nb;	
			}
		}	
		else
		{
			if (i == 5 || vct_getfirstchar(split) != ',')
				machine->information |= ERROR_COLOR;
		}
		vct_del(&split);
		i++;
	}
	vct_del(&split);
}

static int	parser_color(t_vector *vct, t_state_machine *machine)
{
	char		*tab_color[NB_INDIC_COLOR] = {"F", "C"};
	uint8_t		i;
	uint8_t		count;
	t_vector	*split;
	t_vector	*cpy;

	i = 0;
	count = 0;
	while ((split = vct_split(vct, " \t", NO_SEP))
			&& (machine->information & IS_ERROR) == FALSE
			&& machine->state == COLOR)
	{
		if (i == 0)
		{
			while (count < NB_INDIC_COLOR
				&& ft_strequ(vct_getstr(split), tab_color[count]) == FALSE)
				count++;
			if (count == NB_INDIC_COLOR)
				machine->state = MAP;
		}
		else
		{
			cpy = vct_dup(split);
			vct_del(&split);
			if ((split = vct_split(vct, " \t", NO_SEP)) != NULL)
				machine->information |= ERROR_COLOR;
			else
			{
				if (count == 0 && (machine->information & BT_COLOR_F) == FALSE)
					machine->information |= BT_COLOR_F;
				else if (count == 1 && (machine->information & BT_COLOR_C) == FALSE)
					machine->information |= BT_COLOR_C;
				else
					machine->information |= ERROR_COLOR;
				if ((machine->information & IS_ERROR) == FALSE)
				{
					get_color(cpy, machine, count == 0 ? BT_COLOR_F : BT_COLOR_C);
					vct_del(&cpy);
					break ;
				}
			}
			vct_del(&cpy);
		}
		i++;
		vct_del(&split);
	}
	vct_del(&split);
	if (machine->state == COLOR)
	{
		machine->state = RESOLUTION;
		return (SUCCESS);
	}
	return (FAILURE);
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
		return (FAILURE);
	}
	ret = TRUE;
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	if (count_loops_function == 0)
		ret = what_information_map(cpy_vct, vct_getlen(vct), machine);
	count_loops_function++;
	ret = is_map(cpy_vct);
	if (ret == ERROR)
	{
		machine->information |= ERROR_MAP;
		vct_del(&cpy_vct);
		return (FAILURE);
	}
	ret = recuperation_map(cpy_vct, machine);
	if (ret == ERROR)
	{
		machine->information |= ERROR_MAP;
		return (FAILURE);
	}
	vct_del(&cpy_vct);
	return (SUCCESS);
}

int			first_parser(t_state_machine *machine, int fd)
{
	static t_function	function[NB_INFO] = {parser_resolution, parser_texture,
										parser_color, parser_map};
	ssize_t				ret;
	t_vector			*line;

	line = vct_new();
	ret = 0;
	while ((machine->information & IS_ERROR) == FALSE
			&& (ret = vct_readline(line, fd)) > 0)
	{
		machine->info.nb_line++;
		if (line->len == 0 && machine->state != MAP)
			continue ;
		vct_split(NULL, NULL, INIT);
		while ((machine->information & IS_ERROR) == FALSE
			&& function[machine->state](line, machine) == FAILURE)
			vct_split(NULL, NULL, INIT);
	}
	vct_del(&line);
	if (machine->information & IS_ERROR || ret == FAILURE)
	{
		printf_errors(machine->information, machine->info.nb_line);
		return (FAILURE);
	}
	return (SUCCESS);
}
