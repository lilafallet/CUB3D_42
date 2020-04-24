/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:33:48 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/22 16:53:18 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

void		what_bitwaze(t_state_machine *machine, int index)
{
	if (index == NO)
		machine->information |= BT_NO;
	else if (index == SO)
		machine->information |= BT_SO;
	else if (index == WE)
		machine->information |= BT_WE;
	else if (index == EA)
		machine->information |= BT_EA;
	else if (index == S)
		machine->information |= BT_SPR;
}

int	have_all_texture(t_state_machine *machine)
{
	return (machine->information & BT_NO && machine->information & BT_SO &&
		machine->information & BT_WE && machine->information & BT_EA &&
		machine->information & BT_SPR);
}

int what_information_texture(t_vector *vct, size_t clen_text,
								t_state_machine *machine, int ret)
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
	if (tab_len[0] == clen_text && tab_len[1] == clen_text
			&& tab_len[2] == clen_text && tab_len[3] == clen_text
			&& ret == NEXT_OTHERCHAR)
		machine->state = COLOR;
	return (NEXT_OTHERCHAR);
}

int		clean_before(t_vector *vct, char **str_texture, int index,
						t_state_machine *machine)
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
			break ;
		i++;
	}
	if (len != i && len != 0)
	{
		clen_text = vct_clen(vct, str_texture[index][0]);
		index = what_information_texture(vct, clen_text, machine, TRUE);
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
				ret = ERROR;
		}
		else
		{
				machine->state = TEXTURE;
				ret = ERROR;
		}
	}
	return (ret);
}
