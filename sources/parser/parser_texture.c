/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:54:19 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/23 18:59:41 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

int			send_to_function_texture(t_vector *vct,
										char *tab_texture[NB_TEXTURE],
										t_state_machine *machine,
										t_vector *texture)
{
	int		ret;
	int		index;
	size_t	len;

	ret = is_texture(vct, tab_texture, machine);
	index = ret;
	len = vct_getlen(vct);
	if (ret == NEXT_OTHERCHAR)
		what_information_texture(vct, len, machine, ret);
	if (ret >= NO && ret <= S && ret != NEXT_OTHERCHAR)
		ret = pre_process_split(texture, vct, tab_texture[ret]);
	else
		ret = NEXT;
	if (ret != NEXT)
		ret = init_machine_texture(ret, machine, index, vct);
	if (have_all_texture(machine) == TRUE && ret == NEXT)
	{
		ret = TRUE;
		machine->state = MAP;
	}
	return (ret);
}

static int	process_split(t_vector *texture, t_vector *vct, char **ret_str)
{
	int	ret;
	int	count_path;

	count_path = 0;
	ret = TRUE;
	while ((texture = vct_split(vct, PATH, ALL_SEP)) != NULL)
	{
		if (count_path == 1)
		{
			free(*ret_str);
			*ret_str = vct_strdup(texture);
			ret = vct_apply(texture, IS_ASCII) == FALSE ? FALSE : TRUE | NEXT;
			break ; 
		}
		if (ft_strequ(vct_getstr(texture), PATH) == TRUE)
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

static void	final_path(t_vector *cpy_vct, t_vector *vct)
{
	size_t		clen;
	char		*ret_cpy;

	clen = vct_clen(cpy_vct, SLASH);
	ret_cpy = vct_getstr(cpy_vct);
	ret_cpy = ft_strdup(ret_cpy + clen + 1);
	vct_del(&cpy_vct);
	cpy_vct = vct_new();
	vct_addstr(cpy_vct, ret_cpy);
	vct_cpy(vct, cpy_vct);
	vct_del(&cpy_vct);
	free(ret_cpy);
}

int			pre_process_split(t_vector *texture, t_vector *vct,
								char *str_texture)
{
	int			ret;
	char		*ret_str;
	size_t		len;
	int			count_path;
	t_vector	*cpy_vct;
	
	cpy_vct = vct_new();
	ret = TRUE;
	len = ft_strlen(str_texture);
	count_path = 0;
	ret_str = ft_strnstr(vct_getstr(vct), str_texture, vct_getlen(vct));
	vct_addstr(cpy_vct, ret_str + len);
	ret_str = NULL;
	free(ret_str);
	ret = process_split(texture, cpy_vct, &ret_str);
	final_path(cpy_vct, vct);
	free(ret_str);
	return (ret);
}

int			is_texture(t_vector *vct, char **tab_texture,
						t_state_machine *machine)
{
	int		ret;
	char	*ret_str;
	int		index;

	ret = TRUE;
	ret_str = NULL;
	index = 0;
	while (index < NB_TEXTURE) 
	{
		ret_str = ft_strnstr(vct_getstr(vct), tab_texture[index],
								vct_getlen(vct));
		if (ret_str != NULL)
			break ;
		index++;
	}
	if (ret_str == NULL)
		ret = NEXT_OTHERCHAR;
	else if (ret_str != NULL)
		ret = clean_before(vct, tab_texture, index, machine);
	return (ret);
}
