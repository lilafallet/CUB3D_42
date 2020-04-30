/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 22:56:08 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	recuperation_texture(t_state_machine *map, uint8_t count,
		t_vector *split)
{
	if (map->info.str_texture[count] != NULL)
		map->information |= ERROR_TEXTURE_ALREADY;
	else
	{
		map->info.str_texture[count] = vct_strdup(split);
		map->information |= (1 << count);
	}
}

void	is_texture(uint8_t *count, t_vector *split, t_state_machine *map,
		char *tab_texture[NB_TEXTURE])
{
	while (*count < NB_TEXTURE
			&& ft_strequ(vct_getstr(split), tab_texture[*count]) == FALSE)
		*count = *count + 1;
	if (*count == NB_TEXTURE)
		map->state = COLOR;
}


/*t_info	*get_info(t_info *info)
{
	static t_info	*gen_info = NULL;

	if (gen_info == NULL)
		gen_info = info;
	return (gen_info);
}

int		main(void)
{
	t_info	info;

	INIT
	get_info(info);
}
t_info	*info;

info = get_info(NULL);*/
