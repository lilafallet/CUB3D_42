/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textsprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 13:11:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/23 21:34:39 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	count_sprite(t_map *map, t_graph *gr)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->utils.count_line)
	{
		x = 0;
		while (map->recup.tab_map[y][x] != OUT)
		{
			if (map->recup.tab_map[y][x] == SPRITE)
				gr->sp.nb_sprite++;
			x++;
		}
		y++;
	}
}

static void	init_coord_sprite(t_map *map, t_graph *gr)
{
	size_t	x;
	size_t	y;
	size_t	count;

	y = 0;
	count = 0;
	gr->sp.pos = (t_position *)malloc(sizeof(t_position) * gr->sp.nb_sprite);
	if (gr->sp.pos == NULL)
	{
		printf_errors(ERROR_MALLOC_POS, 0, NULL);
		exitred(gr, FAILURE);
	}
	while (y < map->utils.count_line)
	{
		x = 0;
		while (map->recup.tab_map[y][x] != OUT)
		{
			if (map->recup.tab_map[y][x] == SPRITE)
			{
				gr->sp.pos[count].x = x + 0.5;
				gr->sp.pos[count].y = y + 0.5;
				count++;
			}
			x++;
		}
		y++;
	}
}

int		what_texture(t_graph *gr)
{
	if (gr->rting.side == EA && gr->rting.raydirx > 0)
		return (EA);
	else if (gr->rting.side == WE && gr->rting.raydirx < 0)
		return (WE);
	else if (gr->rting.side == NO && gr->rting.raydiry < 0)
		return (NO);
	else
		return (SO);
}

void	get_textures(t_map *map, t_graph *gr)
{
	size_t	i;
	int		w;
	int		h;

	i = 0;
	ft_bzero(gr->text.img, sizeof(int *) * NB_TEXTURE);
	ft_bzero(gr->text.data, sizeof(int *) * NB_TEXTURE);
	while (i < NB_TEXTURE)
	{
		gr->text.img[i] = (int *)mlx_xpm_file_to_image
								(gr->win.mlx_ptr, map->recup.str_texture[i],
									&w, &h);
		if (gr->text.img[i] == NULL)
		{
			printf_errors(ERROR_IMG, 0, NULL);
			exitred(gr, FAILURE);
		}
		gr->text.size[i][WIDTH] = w;
		gr->text.size[i][HEIGHT] = h;
		i++;
	}
	i = 0;
	while (i < NB_TEXTURE)
	{
		gr->text.data[i] = (int *)mlx_get_data_addr(gr->text.img[i],
								&gr->text.bits[i], &gr->text.size_line[i],
								&gr->win.endian);
		if (gr->text.data[i] == NULL)
		{	
			printf_errors(ERROR_DATA, 0, NULL);
			exitred(gr, FAILURE);
		}
		i++;
	}
	count_sprite(map, gr);
	init_coord_sprite(map, gr);
}
