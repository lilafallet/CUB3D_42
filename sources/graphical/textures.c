/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:33:56 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/14 12:19:11 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_textures(t_map *map, t_graph *graph, t_rting *rting)
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
		rting->text_img[i] = mlx_xpm_file_to_image
								(graph->recup.mlx_ptr, map->recup.str_texture[i],
									&w, &h);
		rting->text_size[i][WIDTH] = w;
		rting->text_size[i][HEIGHT] = h;
		/*ft_printf("ptr = %p : text_size[%d][WIDTH] = %d\n", rting->text_img[i],
					i, rting->text_size[i][WIDTH]); */
		/*ft_printf("ptr = %p : text_size[%d][HEIGHT] = %d\n", rting->text_img[i],
					i, rting->text_size[i][HEIGHT]); */
		i++;
	}
	//ft_printf("\n");
	i = 0;
	while (i < NB_TEXTURE)
	{
		rting->text_data[i] = mlx_get_data_addr(rting->text_img[i],
								&graph->recup.bits, &graph->recup.size_line,
								&graph->recup.endian);
		/*ft_printf("rting->text_data[%d] = %p\n", i, rting->text_data[i]); //
		ft_printf("rting->text_img[%d] = %p\n", i, rting->text_img[i]); //
		ft_printf("bits = %d\n", graph->recup.bits); //
		ft_printf("size_line = %d\n", graph->recup.size_line); //
		ft_printf("endian = %d\n\n", graph->recup.endian);*/
		i++;
	}	
}
