/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:57:21 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/17 22:08:26 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

void	ft_free(t_state_machine *machine, t_vector *line)
{
	ft_printf("FT_FREE\n"); //
	vct_del(&line);
	line = NULL;
	free(machine->str_info_final);
	ft_free_tab(NB_RESOLUTION, machine->info.str_resolution);
	ft_free_tab(NB_TEXTURE, machine->info.str_texture);
	ft_free_tab(BUFFER_SIZE, machine->info.str_map);
}
