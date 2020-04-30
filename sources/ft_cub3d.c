/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:43:22 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 22:54:22 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static int	debug_print_map(t_state_machine *map, size_t i, size_t j)
{
	ft_printf("%d%c", map->info.tab_map[i][j],
			(j + 1 == map->info.max_index) ? '\n' : ' '); //DEBUG//
	return (TRUE);
}

static void	debug(t_state_machine *map)
{
	ft_printf("R:\t\t%d %d\n",			map->info.str_resolution[0],
										map->info.str_resolution[1]);
	ft_printf("NO:\t\t%s\n",			map->info.str_texture[0]);
	ft_printf("SO:\t\t%s\n",			map->info.str_texture[1]);
	ft_printf("WE:\t\t%s\n",			map->info.str_texture[2]);
	ft_printf("EA:\t\t%s\n",			map->info.str_texture[3]);
	ft_printf("S:\t\t%s\n",				map->info.str_texture[4]);
	ft_printf("F:\t\t%d %d %d\n",		map->info.tab_color_f[0],
										map->info.tab_color_f[1],
										map->info.tab_color_f[2]);
	ft_printf("C:\t\t%d %d %d\n\n",		map->info.tab_color_c[0],
										map->info.tab_color_c[1],
										map->info.tab_color_c[2]);
	iter_map(map, debug_print_map);
}

static int	ft_cub3d(int fd, t_state_machine *map)
{
	if (first_parser(map, fd) == SUCCESS)
	{
		if (verification_global_map(map) == ERROR)
			printf_errors(map->information, map->info.nb_line);
		else
			debug(map); // DEBUG
	}
	return (SUCCESS);
}

int			main(int ac, char **av)
{
	int				fd;
	t_state_machine		map;

	(void)av;
	ft_bzero(&map, sizeof(map));
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
	if (ft_cub3d(fd, &map) == FAILURE)
	{
		close(fd);
		ft_free(&map, NULL);
		return (EXIT_FAILURE);
	}
	test_minilib(&map);
	ft_free(&map, NULL);
	close(fd);
	return (EXIT_SUCCESS);
}
