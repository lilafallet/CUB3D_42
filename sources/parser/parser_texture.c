/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:54:19 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/17 15:29:50 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

void		what_bitwaze(t_state_machine *machine, int index)
{
	if (index == NO)
		machine->information |= BT_NO;
	else if (index == SO)
		machine->information |= BT_SO;
	else if (index == WE)
		machine->information |= BT_WE;
	else if (index == EA)
		machine->information |= BT_EA;
	else if (index == S)
		machine->information |= BT_SPR;
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
			*ret_str = vct_strdup(texture); /*path apres le "./"*/
			if (vct_apply(texture, IS_ASCII) == FALSE)
				ret = FALSE;
			else
				ret = TRUE | NEXT;
			break ; 
		}
		if (ft_strequ(vct_getstr(texture), PATH) == TRUE)
			count_path++; /*on a trouve le path*/
		if (count_path == 0 && vct_apply(texture, IS_WHITESPACE) == FALSE)
		{
			ret = ERROR; /*char indesirable avant le path*/
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

	clen = vct_clen(cpy_vct, SLASH); /*permet d'avoir l'indice*/
	ret_cpy = vct_getstr(cpy_vct);
	ret_cpy = ft_strdup(ret_cpy + clen + 1); /*permet d'avoir la string apres le
	"./"*/
	vct_del(&cpy_vct);
	cpy_vct = vct_new();
	vct_addstr(cpy_vct, ret_cpy); /*ajout de la nouvelle chaine qui permet
	d'avoir plusieurs "./"*/
	vct_cpy(vct, cpy_vct);
	vct_del(&cpy_vct);
	free(ret_cpy);
}

int			pre_process_split(t_vector *texture, t_vector *vct, char *str_texture)
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
	ret_str = ft_strnstr(vct_getstr(vct), str_texture, vct_getlen(vct)); /*copie
	dans ret_str de la ligne jusqu'au premier charactere de NO,SO,WE,EA ou S*/
	vct_addstr(cpy_vct, ret_str + len); /*cpy_vct = ret_str apres l'indicateur*/
	ret_str = NULL;
	free(ret_str);
	ret = process_split(texture, cpy_vct, &ret_str); /*fonction qui va permettre
	de trouver le path + voir si char indesirable apres l'indicateur +
	ret_str = path apres le "./"*/
	final_path(cpy_vct, vct); /*fonction qui permet d'avoir un path qui contient
	plus d'un "./"*/
	free(ret_str);
	return (ret);
}

int			is_texture(t_vector *vct, char **tab_texture, t_state_machine *machine)
{
	int		ret;
	char	*ret_str;
	int		index;

	ret = TRUE;
	ret_str = NULL;
	index = 0;
	while (index < NB_TEXTURE) 
	{
		/*chercher "NO", "SO", "WE", "EA", "S"*/
		ret_str = ft_strnstr(vct_getstr(vct), tab_texture[index],
								vct_getlen(vct));
		if (ret_str != NULL)
			break ;
		index++; /*recuperation de l'index*/
	}
	if (ret_str == NULL)
		ret = NEXT_OTHERCHAR;
	else if (ret_str != NULL)
	{
		ret = clean_before(vct, tab_texture, index, machine); /*savoir si char
		indesirable avant NO, SO, WE, EA, S*/
	}
	return (ret);
}
