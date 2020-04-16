/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 10:36:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/16 15:35:23 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

int	is_color(t_vector *vct, char **tab_color)
{
	int	index;
	char	*str;

	index = 0;
	str = NULL;
	while (index < NB_INDIC_COLOR)
	{
		str = ft_strnstr(vct_getstr(vct), tab_color[index], vct_getlen(vct));
		if (str != NULL)
			break ;
		index++; /*recup index qui va determiner si il s'agit de F ou de G*/
	}
	return (index);
}

static int	verif_before(t_vector *vct, size_t clen)
{
	size_t	i;
	char	*str;
	int		ret;

	i = 0;
	str = vct_getstr(vct);
	ret = TRUE;
	while (i < clen)
	{
		if (str[i] != SPACE && str[i] != TAB)
			ret = ERROR;
		i++;
	}
	return (ret);
}

static int	error_or_true(t_vector *color, size_t count_loops, size_t count_num)
{
	int				ret;

	ret = TRUE;
	if ((count_loops == 0 || count_loops == 6) &&
			vct_apply(color, IS_WHITESPACE) == FALSE)
		ret = ERROR; /*0+6 doit = WHITESPACE*/
	else if (count_loops == 1 && vct_apply(color, IS_DIGIT) == FALSE)
		ret = ERROR; /*1 doit = COLOR*/
	else if ((count_loops == 2 || count_loops == 4) && vct_apply(color,
				IS_WHITESPACECOMMA) == FALSE)
		ret = ERROR; /*2+4 doit = WHITESPACE || COMA*/
	else if ((count_loops == 3 || count_loops == 5) && vct_apply(color,
				IS_WHITESPACEDIGIT) == FALSE)
		ret = ERROR; /*3+5 doit = WHITESPACE || DIGIT*/
	if (count_num != NB_COLOR && count_loops > 5)
		ret = ERROR; 
	count_loops++;
	return (ret);
}

static int	recuperation_color(t_vector *color, char type_color,
								t_state_machine *machine)
{
	int	ret;
	int	num;
	static size_t	index = 0;
	
	ret = TRUE;
	num = ft_atoi(vct_getstr(color));
	if (num < 0 || num > 255)
		ret = ERROR;
	if (type_color == 'F')
	{
		machine->info.tab_color_f[index] = num;
		printf("RECUPERATION_COLOR -> machine->info.tab_color_f[%zu] = %d\n",
				index, machine->info.tab_color_f[index]); //
		ret = TRUE;
		index++;
	}
	else
	{
		machine->info.tab_color_c[index] = num;	
		printf("RECUPERATION_COLOR -> machine->info.tab_color_c[%zu] = %d\n",
				index, machine->info.tab_color_c[index]); //
		ret = TRUE;
		index++;
	}	
	if (index == NB_COLOR && ret != ERROR)
	{
		if (type_color == 'F')
			machine->information |= BT_COLOR_F;	
		else
			machine->information |= BT_COLOR_C;	
		if (((machine->information & BT_COLOR_F) == TRUE) &&
				((machine->information & BT_COLOR_C == TRUE)))
		{
			/*quand on a trouve les deux (F et C) on passe a la prochaine info*/
			machine->state = MAP;
		}
		index = 0;
	}
	return (ret);
}

static int	split_color(t_vector *vct, char *str, char type_color,
							t_state_machine *machine)
{
	int	ret;
	t_vector	*color;
	t_vector	*cpy_vct;
	size_t		count_num;
	size_t		count_loops;
	size_t		count_comma;

	cpy_vct = vct_new();
	vct_addstr(cpy_vct, str); /*ajout de str (chaine apres F ou C) a cpy_vct*/
	ret = TRUE;
	count_num = 0;
	count_loops = 0;
	count_comma = 0;
	while ((color = vct_split(cpy_vct, ", \t", ALL_SEP)) != NULL) /*remplacer avec TAB ET SPACE*/
	{
		ft_printf("SPLIT_COLOR -> color->str = %s\n", vct_getstr(color)); //
		ret = error_or_true(color, count_loops, count_num); /*fonction qui
		permet de determiner si chaque separation est ce qu'on attend
		(espace/tab, chiffre ou virgule)*/
		if (ret == ERROR)
			break ;
		if (vct_apply(color, IS_DIGIT) == TRUE && count_loops != 0)
		{
			ret = recuperation_color(color, type_color, machine);
			/*fonction qui recupere les couleurs R, G, B*/	
			count_num++;
			if (ret == ERROR)
				break ;
		}
		if (vct_chr(color, COMMA) != FAILURE)
		{
			count_comma++;
			printf("ERROR_OR_TRUE -> count_comma = %zu\n", count_comma); //
		}
		count_loops++;
		vct_del(&color);
	}
	if (count_comma != NB_COMMA)
		ret = ERROR; 
	vct_del(&cpy_vct);
	vct_del(&color);
	return (ret);
}

int	pre_split_color(t_vector *vct, char *str, t_state_machine *machine)
{
	size_t	clen;
	int		ret;
	char	*str_clen;
	char	type_color;

	ret = TRUE; //
	str_clen = NULL;
	clen = vct_clen(vct, str[0]);
	type_color = vct_getcharat(vct, clen); /*recuperation de F ou C*/
	ret = verif_before(vct, clen); /*verif si char indesirable avant indic*/
	if (ret == TRUE)
	{
		str_clen = vct_getstr(vct); /*ajoute vct->str a str_clen*/
		str_clen = ft_strdup(str_clen + clen + 1); /*str_clen= str apres indic*/
		ret = split_color(vct, str_clen, type_color, machine);
	}
	free(str_clen);
	return (ret);
}
