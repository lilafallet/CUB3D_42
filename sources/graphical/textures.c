/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:33:56 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/14 15:25:11 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		gr->text.text_img[i] = mlx_xpm_file_to_image
								(gr->win.recup.mlx_ptr, map->recup.str_texture[i],
									&w, &h);
		gr->text.text_size[i][WIDTH] = w;
		gr->text.text_size[i][HEIGHT] = h;
		//TESTER LE RETOUR = message d'erreur -> wrong type of file
		/*ft_printf("ptr = %p : text_size[%d][WIDTH] = %d\n", gr->text_img[i],
					i, gr->text_size[i][WIDTH]); */
		/*ft_printf("ptr = %p : text_size[%d][HEIGHT] = %d\n", gr->text_img[i],
					i, gr->text_size[i][HEIGHT]); */
		i++;
	}
	//ft_printf("\n");
	i = 0;
	while (i < NB_TEXTURE)
	{
		gr->text.text_data[i] = mlx_get_data_addr(gr->text.text_img[i],
								&gr->win.bits, &gr->win.size_line,
								&gr->win.endian);
		//TESTER LE RETOUR = message d'erreur -> failed to get data
		/*ft_printf("gr->text_data[%d] = %p\n", i, gr->text_data[i]); //
		ft_printf("gr->text_img[%d] = %p\n", i, gr->text_img[i]); //
		ft_printf("bits = %d\n", gr->recup.bits); //
		ft_printf("size_line = %d\n", gr->recup.size_line); //
		ft_printf("endian = %d\n\n", gr->recup.endian);*/
		i++;
	}	
}
