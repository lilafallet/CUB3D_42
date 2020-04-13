/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:43:22 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/13 19:49:59 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <sys/types.h> /*open*/
#include <sys/stat.h> /*open*/
#include <fcntl.h> /*open*/
#include <stdio.h> /*DEBUG*/
#include <unistd.h> /*close*/

static int	process_cub3d(t_state_machine *machine, t_vector *line,
							unsigned long nb_line)
{
	ft_printf("PROCESS_CUB3D\n\n"); //
	first_parser(machine, line);
	if (machine->information & IS_ERROR)
	{
		ft_free(machine, line);
		printf_errors(machine->information, nb_line + 1);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	ft_cub3d(t_state_machine *machine, int fd)
{
	ssize_t				ret;
	t_vector			*line;
	unsigned long		nb_line;

	nb_line = 0;
	line = vct_new();
	while ((ret = vct_readline(line, fd)) > 0)
	{
		if (process_cub3d(machine, line, nb_line) == FAILURE)
			return (FAILURE);
		nb_line++;
	}
	if (hub_verification_map(machine, line, nb_line) == FAILURE)
		return (FAILURE);
	ft_free(machine, line);
	return (SUCCESS);
}

int			main(int ac, char **av)
{
	int				fd;
	t_state_machine	machine;

	(void)av;
	ft_bzero(&machine, sizeof(machine));
	if (ac != 2)
	{
		printf_errors(ERR_USAGE, 0);
		return (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY); /*ouvrir le fichier en mode read only*/
	ft_bzero(&machine, sizeof(machine));
	if (ft_cub3d(&machine, fd) == FAILURE)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
