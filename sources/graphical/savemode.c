/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/13 19:16:44 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <string.h>

int		my_mlx_pixel_reverse(t_graph *gr, t_map *map, int x, int y)
{
	int *color;

	color = gr->win.data + (y * map->recup.resolution[AXE_X] + x);
	return (*(int *)color);
}

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int		write_bmp_header(int fd, int filesize, t_graph *gr, t_map *map)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
	{
		bmpfileheader[i] = (unsigned char)(0);
		i++;
	}
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = map->recup.resolution[AXE_X];
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = map->recup.resolution[AXE_Y];
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

int		write_bmp_data(int fd, t_graph *gr, int pad, t_map *map)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = map->recup.resolution[AXE_Y] - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < map->recup.resolution[AXE_X])
		{
			color = my_mlx_pixel_reverse(gr, map, j, i);
			if (write(fd, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(fd, &zero, pad) < 0)
				return (0);
			j++;
		}
		i--;
	}
	return (1);
}

void		savemode(t_map *map, t_graph *gr)
{
	int			filesize;
	int			fd;
	int			pad;

	pad = (4 - ((int)map->recup.resolution[AXE_X] * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)map->recup.resolution[AXE_X] + pad) *
					(int)map->recup.resolution[AXE_Y]);
	if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, 0777)) == -1)
		return ;
	if (!write_bmp_header(fd, filesize, gr, map))
		return ;
	if (!write_bmp_data(fd, gr, pad, map))
		return ;
	close(fd);
	exitred(gr);
}
