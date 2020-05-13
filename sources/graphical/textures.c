/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:33:56 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/13 18:13:36 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_textures(t_map *map, t_graph *graph, t_rting *rting)
{
	size_t	i;
	int		w;
	int		h;

	i = 0;
//
	for (int j = 0;j < NB_TEXTURE; j++)
	{
		FILE *file = fopen(map->recup.str_texture[j] , "rw");	
	
		if (file == NULL)
			perror("fopen");
		else
		{
			printf("%s: c'est good !\n", map->recup.str_texture[j]);
			fclose(file);
		}
	}
//
	while (i < NB_TEXTURE)
	{
		rting->text_img[i] = mlx_xpm_file_to_image
								(graph->recup.mlx_ptr, map->recup.str_texture[i],
									&w, &h);
		rting->text_size[i][WIDTH] = w;
		rting->text_size[i][HEIGHT] = h;
		ft_printf("ptr = %p : text_size[%d][WIDTH] = %d\n", rting->text_img[i], i, rting->text_size[i][WIDTH]); //
		ft_printf("ptr = %p : text_size[%d][HEIGHT] = %d\n", rting->text_img[i], i, rting->text_size[i][HEIGHT]); //
		i++;
	}	
}
