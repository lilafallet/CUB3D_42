/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textsprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 13:11:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/22 14:35:13 by lfallet          ###   ########.fr       */
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
		//A PROTEGER
		exitred(gr);
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
				/*printf("sprite[%zu]{x %lf, y %lf}\n", count,
							gr->sp.pos[count].x, gr->sp.pos[count].y);*/
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
	{
		//superieur a zero sur x on va vers l'est
		return (EA);
	}
	else if (gr->rting.side == WE && gr->rting.raydirx < 0)
	{	
		//inferieur a zero sur x on va vers l'ouest
		return (WE);
	}	
	else if (gr->rting.side == NO && gr->rting.raydiry < 0)
	{
		//inferieur a zero sur y on va vers le nord
		return (NO);
	}
	else
	{
		//superieur a zero sur y on va vers le sud
		return (SO);
	}
}

void	get_textures(t_map *map, t_graph *gr)
{
	size_t	i;
	int		w;
	int		h;

	i = 0;
	/*for (int j = 0;j < NB_TEXTURE; j++)
	{
		FILE *file = fopen(map->recup.str_texture[j] , "rw");	
	
		if (file == NULL)
			perror("fopen");
		else
		{
			printf("%s: c'est good !\n", map->recup.str_texture[j]);
			fclose(file);
		}
	}*/
	while (i < NB_TEXTURE)
	{
		gr->text.img[i] = mlx_xpm_file_to_image
								(gr->win.mlx_ptr, map->recup.str_texture[i],
									&w, &h);
		if (gr->text.img[i] == NULL)
		{
			//MESSAGE ERREUR
			exitred(gr);
		}
		gr->text.size[i][WIDTH] = w;
		gr->text.size[i][HEIGHT] = h;
		//TESTER LE RETOUR = message d'erreur -> wrong type of file
		/*ft_printf("ptr = %p : size[%d][WIDTH] = %d\n", gr->text.img[i],
					i, gr->text.size[i][WIDTH]);
		ft_printf("ptr = %p : size[%d][HEIGHT] = %d\n", gr->text.img[i],
					i, gr->text.size[i][HEIGHT]);*/
		i++;
	}
	//ft_printf("\n");
	i = 0;
	while (i < NB_TEXTURE)
	{
		gr->text.data[i] = (int *)mlx_get_data_addr(gr->text.img[i],
								&gr->text.bits[i], &gr->text.size_line[i],
								&gr->win.endian);
		if (gr->text.data[i] == NULL)
		{	
			//MESSAGE ERREUR
			exitred(gr);
		}
		//TESTER LE RETOUR = message d'erreur -> failed to get data
		/*ft_printf("gr->data[%d] = %p\n", i, gr->text.data[i]); //
		ft_printf("gr->img[%d] = %p\n", i, gr->text.img[i]); //
		ft_printf("bits = %d\n", gr->win.bits); //
		ft_printf("size_line = %d\n", gr->win.size_line); //
		ft_printf("endian = %d\n\n", gr->win.endian);*/
		i++;
	}
	count_sprite(map, gr);
	init_coord_sprite(map, gr);
}
