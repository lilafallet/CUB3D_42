/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_details.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 17:06:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/10 17:32:23 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	resolution_details(t_vector *resol, char **str_resolution, t_vector *vct)
{
	int	ret;
	int	count_num;
		
	ret = TRUE;
	count_num = 0;
	while ((resol = vct_split(vct, " \t", ALL_SEP)) != NULL)
	{
		if (vct_apply(resol, IS_DIGIT) == TRUE)
		{
			if (count_num <= 1)
			{
				str_resolution[count_num] = vct_strdup(resol);
				count_num++;
			}
			else
				ret = FAILURE;
		}
		else if ((vct_apply(resol, IS_WHITESPACE) == FALSE) &&
				(vct_apply(resol, IS_DIGIT) == FALSE))
			ret = FAILURE;
		vct_del(&resol);
	}
	return (ret);
}
