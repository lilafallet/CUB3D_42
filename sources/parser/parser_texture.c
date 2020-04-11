/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 14:53:41 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/11 17:27:17 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

int	text_next_error(t_vector *vct, char *str_text, t_vector *text)
{
	size_t	i;
	int		ret;

	ret = TRUE;
	ft_printf("vct->str = %s\n", vct_getstr(vct)); //
	ft_printf("text->str = %s\n", vct_getstr(text)); //
	i = vct_clen(vct, str_text[0]);
	//VOIR SI CONTIENT QUE DES ESPACES OU TAB AVANT
	printf("i = %zu\n", i); //
	return (ret);
}

int	is_texture(t_vector *text, t_vector *vct)
{
	int	ret;
	char	*ret_str;
	size_t	index;
	char *texture[5] = {"NO", "SO", "WE", "EA", "S"};
	
	ret = TRUE;
	ret_str = NULL;
	index = 0;
	while (index < 5)
	{
		ret_str = ft_strnstr(vct_getstr(vct), texture[index],vct_getlen(vct));
		if (ret_str != NULL)
			break ;
		index ++;
	}
	if (ret_str == NULL)
		ret = NEXT;
	text_next_error(vct, texture[index], text);
	return (ret);
}
