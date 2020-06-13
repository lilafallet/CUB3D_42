/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/13 20:32:24 by lfallet          ###   ########.fr       */
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

int		bmp_header(t_graph *gr, t_map *map, int fd, int filesize)
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
		return (FAILURE);
	return (SUCCESS);
}

int		bmp_data(t_graph *gr, t_map *map, int fd, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					y;
	int					x;
	int					color;

	y = map->recup.resolution[AXE_Y] - 1;
	/*la boucle se fait a l'envers pour pas que le bmp soit affiche a l'envers 
	en little indian*/
	while (y >= 0)
	{
		x = 0;
		while (x < map->recup.resolution[AXE_X])
		{
			color = get_color(gr, map, x, y);
			if (write(fd, &color, 3) < 0)
				return (FAILURE);
			//ecris les informations sur les couleurs (pixels)
			if (pad > 0 && write(fd, &zero, pad) < 0)
				return (FAILURE);
			//permet de rajouter les octets bidons (entre 1 et 3)
			x++;
		}
		y--;
	}
	return (SUCCESS);
}

void		savemode(t_map *map, t_graph *gr)
{
	int			filesize;
	int			fd;
	int			pad;

	pad = (PIXOFFSET - ((int)map->recup.resolution[AXE_X] * 3) % PIXOFFSET) % 4;
	//permet d'alligner en memoire
	filesize = HEADERSIZE + (OCTET3 * ((int)map->recup.resolution[AXE_X]
					+ pad) * (int)map->recup.resolution[AXE_Y]);
	/*taille du headersize + AXE_X * AXE_Y // on a 24 bits (3 octets) par pixel,
	il se peut que la somme des pixels d'une ligne ne soit pas un multiple de 4.
	Dans ce cas, on rajoute a la fin de la ligne, entre 0 et 3 octets bidons
	pour assurer que la ligne est un multiple de 4 octets*/
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC
						| O_APPEND, 0644);
	//ERROR
	//permet de remplacer un fichier tout en ecrasant toutes les donnees restantes
	if (bmp_header(gr, map, fd, filesize) == FAILURE)
	{
		//ERROR
	}
	if (bmp_data(gr, map, fd, pad) == FAILURE)
	{
		//ERROR
	}
	close(fd);
	exitred(gr);
}
