/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:05:38 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/14 16:59:26 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			not_resolution(t_vector *vct)
{
	char	*str;
	size_t	i;
	int		ret;

	ret = ERROR;
	str = vct_getstr(vct);
	i = 0;
	if (ft_strchr(STRING_CHECK_R, str[0]) != NULL)
		ret = NEXT;
	if (ft_strequ(str, STR_TEXTURE_NO) == TRUE ||
			ft_strequ(str, STR_TEXTURE_SO) == TRUE ||
			ft_strequ(str, STR_TEXTURE_WE) == TRUE ||
			ft_strequ(str, STR_TEXTURE_EA) == TRUE)
		ret = NEXT;
	return (ret);
}

static int	count_num(char **str_resolution, t_vector *resol)
{
	int			ret;
	static int	count_num = 0;

	ret = NEXT | TRUE;
	if (count_num <= 1)
	{
		str_resolution[count_num] = vct_strdup(resol);
		if (str_resolution[0] != NULL && str_resolution[1] != NULL) //
		{
			ft_printf("machine->info.str_resolution[0] = %s\n", str_resolution[0]); //
			ft_printf("machine->info.str_resolution[1] = %s\n", str_resolution[1]); //
		}
		count_num++;
	}
	else
		ret = ERROR;
	return (ret);
}

int	split_resolution(t_vector *resol, char **str_resolution, t_vector *vct)
{
	int	ret;
	int	count;

	ret = NEXT | TRUE;
	count = 0;
	while ((resol = vct_split(vct, " \t", ALL_SEP)) != NULL)
	{
		if (vct_apply(resol, IS_DIGIT) == TRUE) /*si numero*/
		{
			count++;
			ret = count_num(str_resolution, resol); /*si trop ou pas assez de
			numero*/
			if (ret == ERROR)
				break ;
		}
		else if ((vct_apply(resol, IS_WHITESPACE) == FALSE) &&
				(vct_apply(resol, IS_DIGIT) == FALSE)) /*si char indesirable*/
		{
			ret = ERROR;
			break ;
		}
		vct_del(&resol);
	}
	if (count != 2)
		ret = ERROR;
	vct_del(&resol);
	return (ret);
}

int	init_machine_resolution(t_state_machine *machine, int ret)
{
	machine->state = TEXTURE;
	if (ret & TRUE)
	{
		ret &= ~NEXT;
		machine->information |= BT_RESOLUTION;
	}
	return (ret);
}

int	is_resolution(t_vector *resol, t_vector *vct)
{
	int	ret;

	ret = TRUE;
	if (vct_chr(vct, 'R') == FAILURE)
		return (NEXT);
	resol = vct_splitchr(vct, 'R');
	if ((vct_getfirstchar(vct) != ' ') && (vct_getfirstchar(vct) != '\t'))
	{
		vct_del(&resol); /*si il n'y a pas d'espace/tab ou si il y'a un
		caractere indesirable*/
		return (ERROR);
	}
	if (vct_apply(resol, IS_WHITESPACE) == FALSE)
	{
		ret = not_resolution(resol); /*determiner si il s'agit d'une erreur dans
		la resolution ou si il s'agit d'une texture, d'une couleur ou de la
		map*/
	}
	vct_del(&resol);
	return (ret);
}
