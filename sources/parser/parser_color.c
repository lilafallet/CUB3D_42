/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 10:36:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/15 10:48:48 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_color(t_vector *vct, char **tab_color)
{
	int	ret;
	int	index;
	char	*str;

	index = 0;
	str = NULL;
	while (index < NB_INDIC_COLOR)
	{
		str = ft_strnstr(vct_getstr(vct), tab_color[index], vct_getlen(vct));
		if (str != NULL)
			break ;
		index++; /*recup index qui va determiner si il s'agit de F ou de G*/
	}
	ft_printf("IS_COLOR -> str = %s\n", str); //
	return (TRUE);
}
