/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/11 20:23:12 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	savemode(t_map *map, t_graph *gr)
{
	int	fd;
	
	if (!(fd = open("screenshot.bmp", O_RDWR | O_CREAT, 77777)))
		return ;
	//revoir la ligne du dessus
	gr->bmp.pixoffset = (unsigned int)PIXOFFSET;
	gr->bmp.headersize = (unsigned int)HEADERSIZE;
	gr->bmp.planecolor = (short)PLANECOLOR;
	gr->bmp.bpp = (short)BPP;
	gr->bmp.bpp = (short)BPP;
	gr->bmp.imgwidth = map->recup.resolution[AXE_X];	
	gr->bmp.imgheight = map->recup.resolution[AXE_Y];	
	gr->bmp.totalpix = (unsigned)(gr->bmp.imgwidth * gr->bmp.imgheight);
	gr->bmp.buffsize = (unsigned int)(gr->bmp.totalpix * PIXOFFSET);
	//c'est quoi ?
	gr->bmp.totalsize = (unsigned)(gr->bmp.totalpix * PIXOFFSET) + HEADERSIZE;
	gr->bmp.xcolor = XPIXELS;
	gr->bmp.ycolor = YPIXELS;
	ft_memset(&(gr->bmp.header), FILLOF0, HEADERSIZE);
	gr->bmp.header[TYPEFILE0] = 'B';
	gr->bmp.header[TYPEFILE0 + 1] = 'M';
	ft_memcpy(gr->bmp.header + FILESIZE2, &(gr->bmp.totalsize),
				sizeof(unsigned int));
	ft_memcpy(gr->bmp.header + PIXOFFSET10, &(gr->bmp.pixoffset),
				sizeof(unsigned int));
	ft_memcpy(gr->bmp.header + HEADERSIZE14, &(gr->bmp.headersize),
				sizeof(unsigned int));
	ft_memcpy(gr->bmp.header + IMGWIDTH18, &(gr->bmp.imgwidth), sizeof(int));
	ft_memcpy(gr->bmp.header + IMGHEIGHT22, &(gr->bmp.imgheight), sizeof(int));
	ft_memcpy(gr->bmp.header + PLANECOLOR, &(gr->bmp.planecolor),
				sizeof(short));
	ft_memcpy(gr->bmp.header + BPP28, &(gr->bmp.bpp), sizeof(short));
	ft_memcpy(gr->bmp.header + BUFFSIZE34, &(gr->bmp.buffsize), sizeof(short));
	ft_memcpy(gr->bmp.header + XCOLOR38, &(gr->bmp.xcolor), sizeof(int));
	ft_memcpy(gr->bmp.header + YCOLOR42, &(gr->bmp.ycolor), sizeof(int));
}
