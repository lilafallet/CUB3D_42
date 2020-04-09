/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:53:10 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/09 16:57:33 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> /*DEBUG*/

int	hub_verification_map(t_state_machine *machine, t_vector *line, unsigned long nb_line)
{
	int	ret;

	ret = SUCCESS;
	ft_printf("HUB_VERIFICATION_MAP\n"); //
	/*ret = hub_verification(machine->info.str_map, MAP, machine);
	printf("nb_line = %lu\n", nb_line);
	if (machine->information & IS_ERROR)
	{
		ft_free(machine, line);
		printf_errors(machine->information, nb_line + 1); //regler le probleme de ligne pas bonne
		return (FAILURE);
	}*/
	return (ret);		
}
