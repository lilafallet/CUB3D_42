/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/13 16:19:19 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static void	int_to_char(int n, unsigned char *src)
{
	src[0] = (unsigned char)(n);
	src[1] = (unsigned char)(n >> 8);
	src[2] = (unsigned char)(n >> 16);
	src[3] = (unsigned char)(n >> 24);
	//comprendre cette fonction et sinon essaye de faire comme Fred
}

static void	image_bmp(t_graph *gr, t_map *map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	j = 0;
	while (j < map->recup.resolution[AXE_Y])
	{
		i = 0;
		while (i < map->recup.resolution[AXE_X])
		{
			x = i;
			y = map->recup.resolution[AXE_Y] - 1 - j;
			gr->bmp.color = gr->win.data[x + y
								* map->recup.resolution[AXE_X]];
			write(gr->bmp.fd, &gr->bmp.color, 3);
			i++;
		}
		i = 0;
		while (i < (4 - (map->recup.resolution[AXE_X] * 3) % 4) % 4)
		{
			write(gr->bmp.fd, &gr->bmp.pad, 1);
			i++;
		}
		j++;
	}
}

void	savemode(t_map *map, t_graph *gr)
{
	int	image_size;
	int	i;

	i = 0;
	image_size = 3 * map->recup.resolution[AXE_X] * map->recup.resolution[AXE_Y];
	gr->bmp.size = 54 + image_size;
	gr->bmp.image = malloc((sizeof(char) * image_size));
	//A PROTEGER
	ft_memset(gr->bmp.image, 0, image_size);
	gr->bmp.fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	//A PROTEGER
	while (i < 14)
	{
		gr->bmp.header[i] = 0;
		i++;
	}
	gr->bmp.header[0] = 'B';
	gr->bmp.header[1] = 'M';
	gr->bmp.header[10] = 54;
	i = 0;
	while (i < 40)
	{
		gr->bmp.info[i] = 0;
		i++;
	}
	gr->bmp.info[0] = 40;
	gr->bmp.info[12] = 1;
	gr->bmp.info[14] = 24;
	i = 0;
	while (i < 3)
	{
		gr->bmp.pad[i] = 0;
		i++;	
	}
	int_to_char(gr->bmp.size, &gr->bmp.header[2]);
	int_to_char(map->recup.resolution[AXE_X], &gr->bmp.info[4]);
	int_to_char(map->recup.resolution[AXE_Y], &gr->bmp.info[8]);
	write(gr->bmp.fd, gr->bmp.header, 14);
	write(gr->bmp.fd, gr->bmp.info, 40);
	image_bmp(gr, map);
	free(gr->bmp.image);
	close(gr->bmp.fd);
	exitred(gr);
}
