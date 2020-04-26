/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:53:10 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/26 14:29:47 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> /*DEBUG*/

void	printf_errors(unsigned long flag, unsigned long line)
{
	const char		*error[NB_ERROR] = {ERR1, ERR2, ERR3, ERR4, ERR5, ERR6,
										ERR7, ERR8, ERR9, ERR10, ERR11};
	unsigned long	index;
	size_t			i;
	static size_t	loops_function = 0;

	if (loops_function != 0)
		return ;
	if (flag == ERR_USAGE)
	{
		ft_dprintf(STDERR_FILENO, "Usage: %s", ERROR_ARGUMENTS);
		loops_function++;
		return ;
	}
	if (flag == ERR_GLOBAL)
	{
		ft_dprintf(STDERR_FILENO, "Error\n");
		ft_dprintf(STDERR_FILENO, "There's an invalid char somewhere\n");
		loops_function++;
		return ;

	}
	i = 0;
	index = flag >> 24;
	while (i < NB_ERROR)
	{
		if (index & (1 << i))
		{
			ft_dprintf(STDERR_FILENO, "Error\n");
			ft_dprintf(STDERR_FILENO, "[line %ld]: %s", line, error[i]);
		}
		i++;
	}
	loops_function++;
}
