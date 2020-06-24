/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:43:22 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 14:21:08 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int			gestion_parser(int ret, t_vector *line, t_map *map,
							t_state_machine *machine)
{
	if (ret == FAILURE)
	{
		vct_del(&line);
		if (close(map->utils.fd) == FAILURE)
			perror(FAIL_CLOSE_MAP);
		ft_free(map, line);
		exit(EXIT_FAILURE);
	}
	if (machine->info & IS_ERROR || ret == FAILURE)
	{
		printf_errors(machine->info, map->utils.nb_line, line);
		vct_del(&line);
		return (FAILURE);
	}
	return (SUCCESS);
}

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
			printf_errors(machine.info, NO_LINE, NO_VECTOR);
			return (FAILURE);
		}
	}
	return (ret);
}

static int	parser_argument(int ac, char **av, t_map *map)
{
	if (ac < SECOND_ARG || ac > THIRD_ARG)
	{
		if (ac < SECOND_ARG)
			printf_errors(ERROR_ARG_LITTLE, NO_LINE, NO_VECTOR);
		if (ac > THIRD_ARG)
			printf_errors(ERROR_ARG_BIG, NO_LINE, NO_VECTOR);
		return (FAILURE);
	}
	if (is_good_file(av[FIRST_ARG]) == FAILURE)
		return (FAILURE);
	if (ac == THIRD_ARG)
	{
		if (parser_savemode(av[SECOND_ARG], map) == FAILURE)
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
		fd = open(av[FIRST_ARG], O_RDONLY);
	if (ret != FAILURE && fd != FAILURE
			&& (ret = ft_cub3d(fd, &map)) != FAILURE)
		start_graph(&map);
	if (fd == FAILURE)
		perror(FAIL_OPEN_MAP);
	ft_free(&map, NO_VECTOR);
	if (close(fd) == FAILURE)
		perror(FAIL_CLOSE_MAP);
	return (ret == FAILURE || fd == FAILURE ? EXIT_FAILURE : EXIT_SUCCESS);
}
