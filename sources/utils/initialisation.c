/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:57:21 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/09 17:05:35 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

void	ft_free(t_state_machine *machine, t_vector *line)
{
	ft_printf("FT_FREE\n"); //
	(void)machine;
	(void)line;
	/*free(line);
	free(machine->str_info_final);
	ft_free_tab(NB_RESOLUTION, machine->info.str_resolution);	
	ft_free_tab(NB_TEXTURE, machine->info.str_texture);
	ft_free_tab(NB_COLOR, machine->info.str_color_f);
	ft_free_tab(NB_COLOR, machine->info.str_color_c);
	ft_free_tab(BUFFER_SIZE, machine->info.str_map);*/
}
