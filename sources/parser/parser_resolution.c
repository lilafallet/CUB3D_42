/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 14:48:49 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/11 17:11:58 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_next_or_error_resolution(t_vector *vct)
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

static int	is_error(char **str_resolution, t_vector *resol)
{
	int			ret;
	static int	count_num = 0;

	ret = NEXT | TRUE;
	if (count_num <= 1)
	{
		str_resolution[count_num] = vct_strdup(resol);
		count_num++;
	}
	else
		ret = ERROR;
	return (ret);
}

int	resolution_details(t_vector *resol, char **str_resolution, t_vector *vct)
{
	int	ret;

	ret = NEXT | TRUE;
	while ((resol = vct_split(vct, " \t", ALL_SEP)) != NULL)
	{
		if (vct_apply(resol, IS_DIGIT) == TRUE)
		{
			ret = is_error(str_resolution, resol);
			if (ret == ERROR)
				break ;
		}
		else if ((vct_apply(resol, IS_WHITESPACE) == FALSE) &&
				(vct_apply(resol, IS_DIGIT) == FALSE))
		{
			ret = ERROR;
			break ;
		}
		vct_del(&resol);
	}
	vct_del(&resol);
	return (ret);
}

int	is_true_and_next(t_state_machine *machine, int ret)
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
	if (vct_apply(resol, IS_WHITESPACE) == FALSE)
		ret = is_next_or_error_resolution(resol);
	vct_del(&resol);
	return (ret);
}
