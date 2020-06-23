/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:43:22 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/23 15:00:32 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*static int	debug_print_map(t_map *map, size_t i, size_t j,
				t_state_machine *machine)
{
	(void)machine;
	ft_printf("%d%c", map->recup.tab_map[i][j],
			(j + 1 == map->utils.max_index) ? '\n' : ' '); //DEBUG//
	return (TRUE);
}*/

/*static void	debug(t_map *map, t_state_machine *machine)
{
	ft_printf("R:\t\t%d %d\n",			map->recup.resolution[0],
										map->recup.resolution[1]);
	ft_printf("NO:\t\t%s\n",			map->recup.str_texture[0]);
	ft_printf("SO:\t\t%s\n",			map->recup.str_texture[1]);
	ft_printf("WE:\t\t%s\n",			map->recup.str_texture[2]);
	ft_printf("EA:\t\t%s\n",			map->recup.str_texture[3]);
	ft_printf("S:\t\t%s\n",				map->recup.str_texture[4]);
	ft_printf("F:\t\t%d %d %d\n",		map->recup.tab_color_f[0],
										map->recup.tab_color_f[1],
										map->recup.tab_color_f[2]);
	ft_printf("C:\t\t%d %d %d\n\n",		map->recup.tab_color_c[0],
										map->recup.tab_color_c[1],
										map->recup.tab_color_c[2]);
	iter_map(map, debug_print_map, machine);
}*/

static int	ft_cub3d(int fd, t_map *map)
{
	t_state_machine	machine;
	int				ret;

	ft_bzero(&machine, sizeof(machine));
	ret = first_parser(map, fd, &machine);
	if (ret == SUCCESS)
	{
		if (verification_global_map(map, &machine) == ERROR)
		{
			printf_errors(machine.info, 0, NULL);
			return (FAILURE);
		}
		//else
			//debug(map, &machine); // DEBUG
	}
	return (ret);
}

static int	parser_argument(int ac, char **av, t_map *map)
{
	if (ac < 2 || ac > 3)
	{
		if (ac < 2)
			printf_errors(ERR_ARG_LITTLE, 0, NULL);
		if (ac > 3)
			printf_errors(ERR_ARG_BIG, 0, NULL);
		return (FAILURE);
	}
	if (is_good_file(av[1]) == FAILURE)
		return (FAILURE);
	if (ac == 3)
	{
		if (parser_savemode(av[2], map) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int			main(int ac, char **av)
{
	int		fd;
	t_map	map;
	int		ret;

	(void)av;
	fd = 0;
	get_map(&map);
	ft_bzero(&map, sizeof(map));
	ret = parser_argument(ac, av, &map);
	if (ret == SUCCESS)
		fd = open(av[1], O_RDONLY);
	if (ret != FAILURE && fd != FAILURE && (ret = ft_cub3d(fd, &map)) != FAILURE)
		start_graph(&map);
	if (fd == FAILURE)
		perror("Error\nFail to open the map");
	ft_free(&map, NULL);
	close(fd);
	return (ret == FAILURE || fd == FAILURE ? EXIT_FAILURE : EXIT_SUCCESS);
}
