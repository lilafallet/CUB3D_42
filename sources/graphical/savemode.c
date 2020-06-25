/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 17:17:13 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	get_color(t_graph *gr, t_map *map, int x, int y)
{
	int *color;

	color = gr->win.data + (y * map->recup.resolution[AXE_X] + x);
	return (*(int *)color);
}

static void	bmp_header(t_graph *gr, t_map *map, int fd, int filesize)
{
	unsigned char	header[HEADERSIZE];

	ft_bzero(header, HEADERSIZE);
	header[TYPEFILE0] = (unsigned char)('B');
	header[TYPEFILE0 + 1] = (unsigned char)('M');
	ft_int_to_char(header + FILESIZE2, filesize);
	header[PIXOFFSET10] = (unsigned char)(54);
	header[HEADERSIZE14] = (unsigned char)(40);
	ft_int_to_char(header + IMGWIDTH18, map->recup.resolution[AXE_X]);
	ft_int_to_char(header + IMGHEIGHT22, map->recup.resolution[AXE_Y]);
	header[PLANECOLOR27] = (unsigned char)(1);
	header[BPP28] = (unsigned char)(24);
	if (write(fd, header, HEADERSIZE) == FAILURE)
	{
		perror(FAIL_WRITE_HEADER);
		exitred(gr, FAILURE);
	}
}

static void	bmp_data(t_graph *gr, t_map *map, int fd, int pad)
{
	const unsigned char	zero[SIZE_PAD] = {0, 0, 0};
	int					color;

	gr->draw.bmp_y = map->recup.resolution[AXE_Y] - 1;
	while (gr->draw.bmp_y >= 0)
	{
		gr->draw.bmp_x = 0;
		while (gr->draw.bmp_x < map->recup.resolution[AXE_X])
		{
			color = get_color(gr, map, gr->draw.bmp_x, gr->draw.bmp_y);
			if (write(fd, &color, SIZE_PAD) == FAILURE)
			{
				perror(FAIL_WRITE_COLOR);
				exitred(gr, FAILURE);
			}
			if (pad > 0 && write(fd, &zero, pad) == FAILURE)
			{
				perror(FAIL_WRITE_PADING);
				exitred(gr, FAILURE);
			}
			gr->draw.bmp_x++;
		}
		gr->draw.bmp_y--;
	}
}

void		savemode(t_map *map, t_graph *gr)
{
	int			filesize;
	int			fd;
	int			pad;

	pad = (PIXOFFSET - (map->recup.resolution[AXE_X] * SIZE_PAD) % PIXOFFSET)
			% PIXOFFSET;
	filesize = HEADERSIZE + (OCTET3 * map->recup.resolution[AXE_Y]
							* (map->recup.resolution[AXE_X] + pad));
	fd = open(SCREENSHOT, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s: %s\n", SCREENSHOT,
					strerror(errno));
		exitred(gr, FAILURE);
	}
	bmp_header(gr, map, fd, filesize);
	bmp_data(gr, map, fd, pad);
	if (close(fd) == FAILURE)
	{
		perror(FAIL_CLOSE_SCREEN);
		exitred(gr, FAILURE);
	}
	exitred(gr, SUCCESS);
}
