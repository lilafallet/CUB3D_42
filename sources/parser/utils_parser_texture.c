/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:33:48 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/14 17:01:27 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

int		clean_before(t_vector *vct, char **str_texture, int index)
{
	size_t	len;
	char	*cpy_texture;
	size_t	i;

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
		index = NO_CHAR;
	free(cpy_texture);
	return (index);
}

void	init_machine_texture(int ret, t_state_machine *machine, int index,
								t_vector *vct)
{
	if (ret & ERROR)
		machine->information |= ERROR_TEXTURE;
	if (ret & NEXT)
	{
		machine->state = COLOR;
		if (ret & TRUE)
		{
			what_bitwaze(machine, index);
			machine->info.str_texture[index] = vct_strdup(vct);
			ft_printf("machine->information.str_texture[%d] = %s\n", index,
						machine->info.str_texture[index]); //
		}
	}
}
