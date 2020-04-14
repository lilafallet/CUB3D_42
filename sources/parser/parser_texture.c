/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:54:19 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/14 12:56:01 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

void		what_bitwaze(t_state_machine *machine, int index)
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

static int	process_split(t_vector *texture, t_vector *vct, char **ret_str)
{
	int	ret;
	int	count_path;

	ft_printf("PROCESS_SPLIT\n"); //
	count_path = 0;
	ret = TRUE;
	while ((texture = vct_split(vct, "./", ALL_SEP)) != NULL)
	{
		if (count_path == 1)
		{
			*ret_str = vct_strdup(texture);
			ret = (vct_apply(texture, IS_ASCII) == FALSE) ? ERROR : TRUE | NEXT;
		}
		if (ft_strequ(vct_getstr(texture), "./") == TRUE)
			count_path++;
		if (count_path == 0 && vct_apply(texture, IS_WHITESPACE) == FALSE)
		{
			ret = ERROR;
			break ;
		}
		vct_del(&texture);
	}
	vct_del(&texture);
	return (ret);
}

static void	final_path(t_vector *cpy_vct, char *ret_str, t_vector *vct)
{
	size_t		clen;
	char		*ret_cpy;
	t_vector	*new_vct;

	new_vct = vct_new();
	clen = vct_clen(cpy_vct, '/');
	ret_cpy = vct_getstr(cpy_vct);
	ret_cpy = ft_strdup(ret_cpy + clen + 1);
	free(ret_str);
	ret_str = vct_getstr(cpy_vct);
	ret_str = ft_strdup(ret_str + clen + 1);
	vct_addstr(new_vct, ret_str);
	vct_cpy(vct, new_vct);
	vct_del(&cpy_vct);
	vct_del(&new_vct);
	free(ret_str);
	free(ret_cpy);
}

int			texture_details(t_vector *texture, t_vector *vct, char *str_texture)
{
	int			ret;
	char		*ret_str;
	size_t		len;
	int			count_path;
	t_vector	*cpy_vct;
	
	cpy_vct = vct_new();
	ft_printf("TEXTURE_DETAILS\n"); //
	ret = TRUE;
	len = ft_strlen(str_texture);
	count_path = 0;
	ret_str = ft_strnstr(vct_getstr(vct), str_texture, vct_getlen(vct));
	vct_addstr(cpy_vct, ret_str + len);
	ret_str = NULL;
	free(ret_str);
	ret = process_split(texture, cpy_vct, &ret_str);
	vct_del(&texture);
	final_path(cpy_vct, ret_str, vct);
	return (ret);
}

int			is_texture(t_vector *vct, char **tab_texture)
{
	int		ret;
	char	*ret_str;
	int		index;

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
		index++;
	}
	if (ret_str == NULL)
	{
		index++;
		ret = index;
	}
	if (ret_str != NULL)
		ret = texture_next_error(vct, tab_texture, index);
	return (ret);
}
