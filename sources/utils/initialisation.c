/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:57:21 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/25 17:41:09 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

void	ft_free(t_state_machine *machine, t_vector *line)
{
	size_t	i;

	i = 0;
	vct_del(&line);
	line = NULL;
	free(machine->str_info_final);
	ft_free_tab(NB_TEXTURE, machine->info.str_texture);
	ft_free_tab(BUFFER_SIZE, machine->info.str_map);
	while (i < machine->info.max_line)
		free(machine->info.tab_map[i++]);
	free(machine->info.tab_map);
}
