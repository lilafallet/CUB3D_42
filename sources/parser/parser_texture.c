/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 14:53:41 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/12 20:51:35 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

void	what_bitwaze(t_state_machine *machine, size_t index)
{
	ft_printf("WHAT BITWAZE\n"); //	
	if (index == 0)
		machine->information |= BT_NO;
	else if (index == 1)
		machine->information |= BT_SO;
	else if (index == 2)
		machine->information |= BT_WE;
	else if (index == 3)
		machine->information |= BT_EA;
	else if (index == 4)
		machine->information |= BT_SPR;
	printf("machine->information = %lu\n", machine->information); //
}

int	texture_details(t_vector *texture, t_vector *vct, char *str_texture)
{
	int	ret;
	char	*ret_str;
	size_t	len;
	int		count_path;
	t_vector	*cpy_vct;
	char		*ret_cpy;
	t_vector	*new_vct;
	

	ft_printf("TEXTURE_DETAILS\n"); //
	cpy_vct = vct_new();	
	new_vct = vct_new();
	len = ft_strlen(str_texture);
	count_path = 0;
	ret_str = ft_strnstr(vct_getstr(vct), str_texture, vct_getlen(vct));
	vct_addstr(cpy_vct, ret_str + len);
	ret_str = NULL;
	while ((texture = vct_split(cpy_vct, "./", ALL_SEP)) != NULL)
	{
		if (count_path == 1)
		{
			free(ret_str);
			ret_str = vct_strdup(texture);
			ft_printf("texture->str = %s\n", vct_getstr(texture)); //
			ft_printf("cpy_vct->str = %s\n", vct_getstr(cpy_vct)); //
			ft_printf("AFTER PATH\n");
			if (vct_apply(texture, IS_ASCII) == FALSE)
				ft_printf("ASCII IS FALSE\n"); //
			else
			{
				ft_printf("ASCII IS TRUE\n"); //
				ret = TRUE | NEXT;
				break ;
			}
		}
		if (ft_strequ(vct_getstr(texture), "./") == TRUE)
		{
			//ft_printf("FIND PATH\n"); //
			count_path++;
		}
		if (count_path == 0 && vct_apply(texture, IS_WHITESPACE) == FALSE)
		{
		//	ft_printf("BEFORE PATH AND NOT WHITESPACE\n"); //
			ret = ERROR;
			break ;
		}
		vct_del(&texture);
	}
	vct_del(&texture);
	count_path = vct_clen(cpy_vct, '/');
	ft_printf("cpy_vct->str end = %s\n", vct_getstr(cpy_vct)); //
	ft_printf("ret_str = %s\n", ret_str); //
	ft_printf("count_path = %d\n", count_path); //
	ret_cpy = vct_getstr(cpy_vct);
	ret_cpy = ft_strdup(ret_cpy + count_path + 1);
	ft_printf("YOUHOOOOOU\n"); //
	ft_printf("IS FALSE\n"); //
	free(ret_str);
	ret_str = vct_getstr(cpy_vct);
	ret_str = ft_strdup(ret_str + count_path + 1);
	ft_printf("ret_str = %s\n", ret_str); //
	vct_addstr(new_vct, ret_str);
	vct_cpy(vct, new_vct);
	vct_del(&cpy_vct);
	vct_del(&new_vct);
	free(ret_str);
	free(ret_cpy);
	return (ret);
}

int	texture_next_error(t_vector *vct, char **str_texture, size_t index, t_vector *texture)
{
	size_t	len;
	int		ret;
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
	if (len != i )
		index = FAILURE;
	free(cpy_texture);
	return (index);
}

int	is_texture(t_vector *texture, t_vector *vct, char **tab_texture)
{
	int		ret;
	char	*ret_str;
	size_t	index;

	ft_printf("IS_TEXTURE\n"); //	
	ret = TRUE;
	ret_str = NULL;
	index = 0;
	while (index < 5)
	{
		ret_str = ft_strnstr(vct_getstr(vct), tab_texture[index],
								vct_getlen(vct));
		if (ret_str != NULL)
			break ;
		index ++;
	}
	if (ret_str == NULL)
	{
		index++;
		ret = index;
	}
	if (ret_str != NULL)
		ret = texture_next_error(vct, tab_texture, index, texture);
	return (ret);
}
