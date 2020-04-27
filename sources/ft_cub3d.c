/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:43:22 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/26 16:31:21 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static int	debug_print_map(t_state_machine *machine, size_t i, size_t j)
{
	ft_printf("%d%c", machine->info.tab_map[i][j],
			(j + 1 == machine->info.max_index) ? '\n' : ' '); //DEBUG//
	return (TRUE);
}

static void	debug(t_state_machine *machine)
{
	ft_printf("R:\t\t%d %d\n",			machine->info.str_resolution[0],
										machine->info.str_resolution[1]);
	ft_printf("NO:\t\t%s\n",			machine->info.str_texture[0]);
	ft_printf("SO:\t\t%s\n",			machine->info.str_texture[1]);
	ft_printf("WE:\t\t%s\n",			machine->info.str_texture[2]);
	ft_printf("EA:\t\t%s\n",			machine->info.str_texture[3]);
	ft_printf("S:\t\t%s\n",				machine->info.str_texture[4]);
	ft_printf("F:\t\t%d %d %d\n",		machine->info.tab_color_f[0],
										machine->info.tab_color_f[1],
										machine->info.tab_color_f[2]);
	ft_printf("C:\t\t%d %d %d\n\n",		machine->info.tab_color_c[0],
										machine->info.tab_color_c[1],
										machine->info.tab_color_c[2]);
	iter_map(machine, debug_print_map);
}

static int	ft_cub3d(int fd)
{
	t_state_machine	machine;

	ft_bzero(&machine, sizeof(machine));
	if (first_parser(&machine, fd) == SUCCESS)
	{
		if (verification_global_map(&machine) == ERROR)
			printf_errors(machine.information, machine.info.nb_line);
		else
			debug(&machine); // DEBUG
	}
	ft_free(&machine, NULL);
	return (SUCCESS);
}

int			main(int ac, char **av)
{
	int				fd;

	(void)av;
	if (ac < 2 || ac > 3)
	{
		printf_errors(ERR_ARG, 0);
		return (EXIT_FAILURE);
	}
	if (is_good_file(av[1]) == FAILURE)
		return (EXIT_FAILURE);
	fd = open(av[1], O_RDONLY);
	if (ac == 3)
	{
		if (what_second_argument(av[2]) == FAILURE)
			return (EXIT_FAILURE);
	}
	if (ft_cub3d(fd) == FAILURE)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	ft_printf("c est ici que tu rentres ici ?\n"); //
	close(fd);
	return (EXIT_SUCCESS);
}
