/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/23 21:55:30 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <string.h>

static int		get_color(t_graph *gr, t_map *map, int x, int y)
{
	int *color;

	color = gr->win.data + (y * map->recup.resolution[AXE_X] + x);
	return (*(int *)color);
}

static void			bmp_header(t_graph *gr, t_map *map, int fd, int filesize)
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
		perror("Error\nFail to write the header on the bmp file");
		exitred(gr, FAILURE);
	}
}

static void		bmp_data(t_graph *gr, t_map *map, int fd, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					y;
	int					x;
	int					color;

	y = map->recup.resolution[AXE_Y] - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < map->recup.resolution[AXE_X])
		{
			color = get_color(gr, map, x, y);
			if (write(fd, &color, 3) < 0)
			{
				perror("Error\nFail to write color the bmp file");
				exitred(gr, FAILURE);
			}
			if (pad > 0 && write(fd, &zero, pad) < 0)
			{
				perror("Error\nFail to write the pading the bmp file");
				exitred(gr, FAILURE);
			}
			x++;
		}
		y--;
	}
}

void		savemode(t_map *map, t_graph *gr)
{
	int			filesize;
	int			fd;
	int			pad;

	pad = (PIXOFFSET - ((int)map->recup.resolution[AXE_X] * 3) % PIXOFFSET) % 4;
	filesize = HEADERSIZE + (OCTET3 * ((int)map->recup.resolution[AXE_X]
					+ pad) * (int)map->recup.resolution[AXE_Y]);
	fd = open(SCREENSHOT, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s: %s\n", SCREENSHOT, strerror(errno));
		exitred(gr, FAILURE);
	}
	bmp_header(gr, map, fd, filesize);
	bmp_data(gr, map, fd, pad);
	if (close(fd) == FAILURE)
	{
		perror("Error\nFail to close the screenshot");
		exitred(gr, FAILURE);
	}
	exitred(gr, SUCCESS);
}
