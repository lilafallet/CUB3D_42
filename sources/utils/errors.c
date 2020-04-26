/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:53:10 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/26 16:34:59 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> /*DEBUG*/

int		is_good_file(char *str)
{
	size_t	len;
	int		ret;

	ret = SUCCESS;
	len = ft_strlen(str);
	if (len <= 4)
		ret = FAILURE;
	if (ret != FAILURE)
	{
		if (ft_strequ(str + len - 4, ".cub") == FALSE)
			ret = FAILURE;
	}
	if (ret == FAILURE)
		printf_errors(ERR_FORMAT, 0);
	return (ret);
}

int		what_second_argument(char *argument)
{
	if (ft_strequ(argument, "--save") == TRUE)
	{
		printf_errors(ERR_SAVE, 0);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	not_machine(unsigned long flag)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (flag == ERR_ARG)
		ft_dprintf(STDERR_FILENO,"%s", ERROR_ARGUMENTS);
	else if (flag == ERR_GLOBAL)
		ft_dprintf(STDERR_FILENO,"%s", ERROR_STR_GLOBAL);
	else if (flag == ERR_SAVE)
		ft_dprintf(STDERR_FILENO,"%s", ERROR_ARGUMENT_SAVE);
	else if (flag == ERR_FORMAT)
		ft_dprintf(STDERR_FILENO,"%s", ERROR_ARGUMENT_FORMAT);
}

void	printf_errors(unsigned long flag, unsigned long line)
{
	const char		*error[NB_ERROR] = {ERR1, ERR2, ERR3, ERR4, ERR5, ERR6,
										ERR7, ERR8, ERR9, ERR10, ERR11};
	unsigned long	index;
	size_t			i;
	static size_t	loops_function = 0;

	i = 0;
	if (loops_function != 0)
		return ;
	if (flag == ERR_ARG || flag == ERR_SAVE || flag == ERR_FORMAT
		|| flag == ERR_GLOBAL)
		not_machine(flag);
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
