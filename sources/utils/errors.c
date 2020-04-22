/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:53:10 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/22 14:12:13 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> /*DEBUG*/

void	printf_errors(unsigned long flag, unsigned long line)
{
	const char		*error[NB_ERROR] = {ERR1, ERR2, ERR3, ERR4};
	unsigned long	index;
	size_t			i;

	if (flag == ERR_USAGE)
	{
		ft_dprintf(STDERR_FILENO, "Usage: %s\n", ERROR_ARGUMENTS);
		return ;
	}
	i = 0;
	index = flag >> 24;
	while (i < NB_ERROR)
	{
		if (index & (1 << i))
			ft_dprintf(STDERR_FILENO, "Error [line %ld]: %s\n", line, error[i]);
		i++;
	}
}
