/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:33:48 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/16 20:47:35 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

static int what_information_texture(t_vector *vct, size_t clen_text, t_state_machine *machine)
{
	const char	*tab_other_texture[3] = {"R", "F", "C"};
	size_t	tab_len[4];
	size_t	i;
	size_t	index;

	i = 0;	
	while (i < 3)
	{
		tab_len[i] = vct_clen(vct, tab_other_texture[i][0]);
		i++;
	}
	tab_len[3] = clen_text;
	index = ft_bubblesort_minindex(tab_len, 4);
	if (index == 0)
		machine->state = RESOLUTION; 
	if (index == 1 || index == 2)
		machine->state = COLOR; 
	return (NEXT_OTHERCHAR);
}

int		clean_before(t_vector *vct, char **str_texture, int index, t_state_machine *machine)
{
	size_t	len;
	char	*cpy_texture;
	size_t	i;
	size_t	clen_text;

	i = 0;
	cpy_texture = ft_memdup(vct_getstr(vct), vct_getlen(vct));
	len = vct_clen(vct, str_texture[index][0]);
	while (i < len)
	{
		if (ft_iswhitespace(cpy_texture[i]) == FALSE)
			break ; /*voir si avant NO,SO,WE,WA,S si il y a char indesirable*/
		i++;
	}
	if (len != i && len != 0) /*si il y a un char indesirable*/
	{
		clen_text = vct_clen(vct, str_texture[index][0]);
		index = what_information_texture(vct, clen_text, machine);
	}
	free(cpy_texture);
	return (index);
}

int	init_machine_texture(int ret, t_state_machine *machine, int index,
								t_vector *vct)
{
	if (ret & ERROR)
		machine->information |= ERROR_TEXTURE;
	if (ret & NEXT)
	{
		if (ret & TRUE)
		{
			what_bitwaze(machine, index);
			machine->info.str_texture[index] = vct_strdup(vct);
		}
		if (machine->information & BT_NO && machine->information & BT_SO &&
			machine->information & BT_WE && machine->information & BT_EA &&
			machine->information & BT_SPR)
		{
				machine->state = COLOR;
				ret = NEXT;
		}
		else
		{
				machine->state = TEXTURE;
				ret = ERROR;
		}
	}
	return (ret);
}
