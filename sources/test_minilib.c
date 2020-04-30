/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 14:39:03 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 19:54:03 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

int		deal_key(int key, void *param)
{
	ft_putchar_fd('X', 1);
	(void)key;
	(void)param;
	return (SUCCESS);
}

void    my_pixel_put_to_image(unsigned long img_color, char *data, int sizeline,
								int bpp, int x, int y)
{
	unsigned char color1;
	unsigned char color2;
	unsigned char color3;
	color1 = (img_color & color_total) >> 24;
	color2 = (img_color & color_total) >> 16;
	color3 = (img_color & color_total) >> 8;
	data[y * sizeline + x * bpp / 8 ] = color1;
	data[y * sizeline + x * bpp / 8 + 1] = color2;
	data[y * sizeline + x * bpp / 8 + 2] = color3;
}
void	test_minilib(t_state_machine *machine)
{
	void  *mlx_ptr;
	void  *win_ptr;
	void  *img_ptr;
	char  *data;
	int   bpp;
	int   sizeline;
	int   endian;
	unsigned long img_color;
	int   x;
	int   y;
	int		color_total;

	x = 0;
	y = 0;
	color_total = machine->info.tab_color_f[0]
					+ (machine->info.tab_color_f[1] << 8)
					+ (machine->info.tab_color_f[2] << 16);
	ft_printf("%x\n", color_total); //
	mlx_ptr = mlx_init();
	img_ptr = mlx_new_image(mlx_ptr, machine->info.str_resolution[AXE_X],
								machine->info.str_resolution[AXE_Y]);
	data = mlx_get_data_addr(img_ptr, &bpp, &sizeline, &endian);
	img_color = mlx_get_color_value(mlx_ptr, color_total);
	while (x < machine->info.str_resolution[AXE_X])
	{
		my_pixel_put_to_image(img_color, data, sizeline, bpp, x, y);
		x++;
		if (x == machine->info.str_resolution[AXE_X] &&
				y < machine->info.str_resolution[AXE_Y])
		{
			x = 0;
			y++;
		}
	}
	win_ptr = mlx_new_window(mlx_ptr, machine->info.str_resolution[AXE_X],
				machine->info.str_resolution[AXE_Y], "NOM A CHANGER");
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	while (42)
	{
	}
}
