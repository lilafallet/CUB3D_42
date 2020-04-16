/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/16 16:39:49 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

static int	parser_resolution(t_vector *vct, t_state_machine *machine)
{
	t_vector	*resol;
	int			ret;
	t_vector	*cpy_vct;

	ft_printf("PARSER_RESOLUTION\n"); //
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	resol = NULL;
	ret = TRUE;
	ret = is_resolution(resol, cpy_vct); /*appelle fonction qui va permettre de
	dire si il s'agit de la resolution ou non (TRUE ou ERROR)*/
	if (ret != ERROR && ret != NEXT) /*si il s'agit bien de la resolution*/
	{
		ret = split_resolution(resol, machine->info.str_resolution, cpy_vct);
		/*utilisation de la fonction split pour trouver chaque nombre et
		determine si 2 nombres ou plus ou moins (ERROR)*/
	}
	if (ret & NEXT)
	{
		ret = init_machine_resolution(machine, ret); /*initialisation de
		machine->state et machine->information*/
	}
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

	ft_printf("PARSER_TEXTURE\n"); //
	texture = vct_new();
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	ret = is_texture(cpy_vct, tab_texture); /*appelle fonction qui va permettre
	de determiner si il s'agit d'une texture ou non (TRUE or ERROR)*/
	index = ret; /*ret vaut l'indice du tableau des textures
	0 = NO
	1 = SO
	2 = WE
	3 = EA
	4 = SPR*/
	if (ret >= NO && ret <= S) /*TRUE*/
	{
		ret = pre_process_split(texture, cpy_vct, tab_texture[ret]); /*utilisation
		de la fonction split pour trouver le path et integration du path dans
		la machine*/
	}
	else
		ret = NEXT;
	ret = init_machine_texture(ret, machine, index, cpy_vct); /*initialisation de
	machine->state et machine->information*/
	ft_printf("machine->information.str_texture[%d] = %s\n", index,
				machine->info.str_texture[index]); //
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

	ft_printf("PARSER_COLOR\n"); //
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	ret = is_color(cpy_vct, tab_color);
	index = ret;
	if (ret <= COLOR_F && ret >= COLOR_C) /*si F ou C*/
		ret = TRUE;
	else /*si pas trouve F ou C*/
		ret = NEXT;
	if (ret == TRUE) /*rentre seulement si on a trouve F ou C*/
	{
		ret = pre_split_color(cpy_vct, tab_color[index], machine); 
		/*fonction qui permet de determiner si il s'agit de l'indication F ou C
		+ avoir la chaine de caractere apres l'indication F ou C + split +
		recuperation des couleurs */
	}
	if (ret == ERROR)
		machine->information |= ERROR_COLOR;
	if (ret == TRUE && ((machine->information & BT_COLOR_F == FALSE ||
			machine->information & BT_COLOR_C == FALSE)))
		ret = ERROR;
	vct_del(&cpy_vct);
	return (ret);	
}

static int	parser_map(t_vector *vct, t_state_machine *machine)
{
	int				ret;
	static size_t	index = 0;
	int				position;

	ret = TRUE;
	ft_printf("PARSER_MAP\n"); //
	(void)index;
	(void)position;
	(void)vct;
	/*machine->info.str_map[index] = ft_memdup(str, ft_strlen(str));
	printf("machine->info.str_map[%lu] = %s\n", index, machine->info.str_map[index]); //
	position = what_position(machine->info.str_map[index],
								machine->info.str_position);
	printf("position = %d\n\n", position); //
	if (position != FAILURE)
		machine->information |= (unsigned long)((1 << position) << 20);
	index++;*/
	machine->state = RESOLUTION;
	return (ret);
}

int			first_parser(t_state_machine *machine, t_vector *line)
{
	static t_function	function[4] = {parser_resolution, parser_texture,
										parser_color, parser_map};
	static int			nb_line = 1; //
	int					ret;
	int					i;

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
