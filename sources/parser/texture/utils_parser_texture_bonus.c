/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_texture_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:21:24 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:21:25 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	recuperation_texture(t_state_machine *machine, uint8_t count,
		t_vector *split, t_map *map)
{
	if (map->recup.str_texture[count] != NULL)
		machine->info |= ERROR_TEXTURE_ALREADY;
	else
	{
		map->recup.str_texture[count] = vct_strdup(split);
		machine->info |= (1 << count);
	}
}

void	is_texture(uint8_t *count, t_vector *split, t_state_machine *machine,
		const char *tab_texture[NB_TEXTURE])
{
	while (*count < NB_TEXTURE
			&& ft_strequ(vct_getstr(split), (char *)tab_texture[*count])
							== FALSE)
		*count = *count + 1;
	if (*count == NB_TEXTURE)
		machine->state = COLOR;
}
