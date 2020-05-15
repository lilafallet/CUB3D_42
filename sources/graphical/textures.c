/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:33:56 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/15 12:44:16 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calcul_texture(t_graph *gr)
{
	return (gr->rting.side == 0 ? gr->rting.posy + gr->rting.perpwalldist
								* gr->rting.raydiry
							: gr->rting.posx + gr->rting.perpwalldist
								* gr->rting.raydirx);
}

int		what_texture(t_graph *gr)
{
	if (gr->rting.side == 1 && gr->rting.raydirx > 0)
		return (EA);
	else if (gr->rting.side == 1 && gr->rting.raydirx < 0)
		return (WE);
	else if (gr->rting.side == 0 && gr->rting.raydirx < 0)
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
		gr->text.size[i][WIDTH] = w;
		gr->text.size[i][HEIGHT] = h;
		//TESTER LE RETOUR = message d'erreur -> wrong type of file
		/*ft_printf("ptr = %p : size[%d][WIDTH] = %d\n", gr->img[i],
					i, gr->size[i][WIDTH]); */
		/*ft_printf("ptr = %p : size[%d][HEIGHT] = %d\n", gr->img[i],
					i, gr->size[i][HEIGHT]); */
		i++;
	}
	//ft_printf("\n");
	i = 0;
	while (i < NB_TEXTURE)
	{
		gr->text.data[i] = (int *)mlx_get_data_addr(gr->text.img[i],
								&gr->text.bits[i], &gr->text.size_line[i],
								&gr->win.endian);
		//TESTER LE RETOUR = message d'erreur -> failed to get data
		/*ft_printf("gr->data[%d] = %p\n", i, gr->data[i]); //
		ft_printf("gr->img[%d] = %p\n", i, gr->img[i]); //
		ft_printf("bits = %d\n", gr->recup.bits); //
		ft_printf("size_line = %d\n", gr->recup.size_line); //
		ft_printf("endian = %d\n\n", gr->recup.endian);*/
		i++;
	}	
}
