/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/25 18:10:41 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	recuperation_texture(t_state_machine *machine, uint8_t count,
		t_vector *split)
{
	if (machine->info.str_texture[count] != NULL)
		machine->information |= ERROR_TEXTURE;
	else
	{
		machine->info.str_texture[count] = vct_strdup(split);
		machine->information |= (1 << count);
	}
}

void	is_texture(uint8_t *count, t_vector *split, t_state_machine *machine,
		char *tab_texture[NB_TEXTURE])
{
	while (*count < NB_TEXTURE
			&& ft_strequ(vct_getstr(split), tab_texture[*count]) == FALSE)
		*count = *count + 1;
	if (*count == NB_TEXTURE)
		machine->state = COLOR;
}
