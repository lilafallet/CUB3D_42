/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:53:10 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 15:20:59 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>

void		error(t_map *map, unsigned long flag, t_vector *vct)
{
	if (flag == ERROR_MALLOC_CPYTAB)
	{
		printf_errors(ERROR_MALLOC_CPYTAB, NO_LINE, NO_VECTOR);
		ft_free(map, NO_VECTOR);
		exit(EXIT_FAILURE);
	}
	if (flag == ERROR_GLOBAL)
	{
		printf_errors(ERROR_GLOBAL, map->utils.nb_line, vct);
		ft_free(map, NO_VECTOR);
		exit(EXIT_FAILURE);
	}
}

int			is_good_file(char *str)
{
	size_t	len;
	int		ret;

	ret = SUCCESS;
	len = ft_strlen(str);
	if (len <= SIZE_FORMAT)
		ret = FAILURE;
	if (ret != FAILURE)
	{
		if (ft_strequ(str + len - SIZE_FORMAT, STR_FORMAT) == FALSE)
			ret = FAILURE;
	}
	if (ret == FAILURE)
		printf_errors(ERROR_FORMAT, NO_LINE, NO_VECTOR);
	return (ret);
}

int			parser_savemode(char *argument, t_map *map)
{
	if (ft_strequ(argument, STR_SAVE) == FALSE)
	{
		map->utils.save_mode = FALSE;
		printf_errors(ERROR_SAVE, NO_LINE, NO_VECTOR);
		return (FAILURE);
	}
	map->utils.save_mode = TRUE;
	return (SUCCESS);
}

static void	process_printf_errors(unsigned long index, t_vector *line,
									unsigned long nb_line)
{
	const char		*error[NB_ERROR] = {ERR1, ERR2, ERR3, ERR4, ERR5, ERR6,
										ERR7, ERR8, ERR9, ERR10, ERR11, ERR12,
										ERR13, ERR14, ERR15, ERR16, ERR17,
										ERR18, ERR19, ERR20, ERR21, ERR22,
										ERR23, ERR24, ERR25, ERR26, ERR27,
										ERR28};
	size_t			i;

	i = 0;
	while (i < NB_ERROR)
	{
		if (index & (1 << i))
		{
			ft_dprintf(STDERR_FILENO, "Error\n");
			if (line != NULL && nb_line != 0)
			{
				ft_dprintf(STDERR_FILENO, "[line %ld]: ", nb_line);
				vct_print_fd(line, STDERR_FILENO);
				ft_dprintf(STDERR_FILENO, " -> ");
			}
			ft_dprintf(STDERR_FILENO, "%s", error[i]);
			break ;
		}
		i++;
	}
}

void		printf_errors(unsigned long flag, unsigned long nb_line,
							t_vector *line)
{
	unsigned long	index;
	static size_t	loops_function = 0;

	if (loops_function != 0)
		return ;
	index = flag >> 24;
	process_printf_errors(index, line, nb_line);
}
