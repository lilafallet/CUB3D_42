/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/13 12:47:53 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	get_pixel(t_graph *gr, unsigned int x, unsigned int y)
{
	int	ptr;

	ptr = *(int*)(gr->win.data + (4 * (int)gr->win.screenwidth
			* ((int)gr->win.screenheight - 1 - y)) + (4 * x));
	return ((ptr & 0xFF0000) | (ptr & 0x00FF00) | (ptr & 0x0000FF));
	//comprendre tout ce charabia
}

static void	int_to_char(int n, unsigned char *src)
{
	src[0] = (unsigned char)(n);
	src[1] = (unsigned char)(n >> 8);
	src[2] = (unsigned char)(n >> 16);
	src[3] = (unsigned char)(n >> 24);
	//comprendre cette fonction et sinon essaye de faire comme Fred
}

void	savemode(t_map *map, t_graph *gr)
{
	int				fd;
	int				filesize;
	int				buffer;
	int				header;
	size_t			y;
	unsigned char	data[HEADERSIZE];
	unsigned char	zero[3]; //pourquoi 3 ?
	size_t			x;
	int				color;

	buffer = (PIXOFFSET - (map->recup.resolution[AXE_X] * 3) % PIXOFFSET)
				% PIXOFFSET;
	//pourquoi vaut 0 ?
	//a quoi correspond 3
	printf("buffer = %d\n", buffer); //
	filesize = HEADERSIZE + (3 * (map->recup.resolution[AXE_X] + buffer)
				* map->recup.resolution[AXE_Y]);
	//a quoi correspond 3
	printf("filesize = %d\n", filesize); //
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,
						0666)) < 0)
		return ;
	//comprendre tous les O et 0666
	ft_bzero(data, HEADERSIZE);
	data[TYPEFILE0] = (unsigned char)'B';
	data[TYPEFILE0 + 1] = (unsigned char)'M';
	int_to_char(filesize, data + FILESIZE2);
	//permet d'avoir l'adresse de filesize ?
	data[PIXOFFSET10] = (unsigned char)HEADERSIZE;
	//represente le decalage le decalage actuel de pixel dans le bit
	data[HEADERSIZE14] = (unsigned char)INFODATASIZE;
	//la taille en bytes du header
	int_to_char(map->recup.resolution[AXE_X], data + IMGWIDTH18);
	int_to_char(map->recup.resolution[AXE_Y], data + IMGHEIGHT22);
	data[PLANECOLOR26] = (unsigned char)PLANECOLOR;
	data[BPP28] = (unsigned char)BPP;
	//nombre de bits qu'un pixel prend
	write(fd, data, HEADERSIZE);
	ft_bzero(zero, 3);
	y = 0;
	while (y < map->recup.resolution[HEIGHT])
	{
		x = 0;
		while (x < map->recup.resolution[WIDTH])
		{
			color = get_pixel(gr, y, x);
			write(fd, &color, 3);
			write(fd, &zero, buffer);
			x++; 
		}
		y++;
	}
	close(fd);
	//exitred(gr);
}
