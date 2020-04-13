/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:33:48 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/13 19:59:10 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

int		texture_next_error(t_vector *vct, char **str_texture, int index)
{
	size_t	len;
	char	*cpy_texture;
	size_t	i;

	ft_printf("TEXTURE_NEXT_ERROR\n"); //	
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
		index = NO_CHAR;
	free(cpy_texture);
	return (index);
}

void	is_next_error(int ret, t_state_machine *machine, int index, t_vector *vct)
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

int		process_texture(int ret, t_vector *vct, char **tab_texture)
{
	t_vector	*texture;

	ft_printf("PROCESS_TEXTURE\n"); //
	texture = vct_new();
	if (ret >= 0 && ret <= 4)
		ret = texture_details(texture, vct, tab_texture[ret]);
	else
		ret = (ret == NO_CHAR ? ERROR : NEXT | TRUE);
	return (ret);
}
