/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_details.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 17:06:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/10 22:27:20 by lfallet          ###   ########.fr       */
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

int	resolution_details(t_vector *resol, char **str_resolution, t_vector *vct)
{
	int	ret;
	int	count_num;
		
	ret = NEXT | TRUE;
	count_num = 0;
	while ((resol = vct_split(vct, " \t", ALL_SEP)) != NULL)
	{
		ft_printf("resol->str = %s\n", resol->str); //
		if (vct_apply(resol, IS_DIGIT) == TRUE)
		{
			if (count_num <= 1)
			{
				str_resolution[count_num] = vct_strdup(resol);
				count_num++;
			}
			else
			{
				ft_printf("TROP DE NOMBRE --> ERROR\n"); //
				ret = ERROR; //GARDER FAILURE
				break ;
			}
		}
		else if ((vct_apply(resol, IS_WHITESPACE) == FALSE) &&
				(vct_apply(resol, IS_DIGIT) == FALSE))
		{
			//ret = is_next_or_error_resolution(resol);
			ret = ERROR;
			ft_printf("CHAR NON VOULUE -> ret = %d\n", ret); //
			break ;
		}
		vct_del(&resol);
	}
	vct_del(&resol);
	return (ret);
}
