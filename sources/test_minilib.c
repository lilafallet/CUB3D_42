/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 14:39:03 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 20:52:42 by lfallet          ###   ########.fr       */
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
	int color1;
	int color2;
	int	color3;

	x = 0;
	y = 0;
	color_total = machine->info.tab_color_f[R]
					+ (machine->info.tab_color_f[G] << 8)
					+ (machine->info.tab_color_f[B] << 16);
	ft_printf("%x\n", color_total);
	ft_printf("COLOR R = %d\n", machine->info.tab_color_f[R]); //
	ft_printf("COLOR G = %d\n", machine->info.tab_color_f[G]); //
	ft_printf("COLOR B = %d\n", machine->info.tab_color_f[B]); //
	mlx_ptr = mlx_init();
	img_ptr = mlx_new_image(mlx_ptr, machine->info.str_resolution[AXE_X],
								machine->info.str_resolution[AXE_Y]);
	data = mlx_get_data_addr(img_ptr, &bpp, &sizeline, &endian);
	img_color = mlx_get_color_value(mlx_ptr, color_total);
	color1 = machine->info.tab_color_f[B];
	color2 = machine->info.tab_color_f[G];
	color3 = machine->info.tab_color_f[R];
	ft_printf("color1 = %d\n", color1); //
	ft_printf("color2 = %d\n", color2); //
	ft_printf("color3 = %d\n", color3); //
	while (x < machine->info.str_resolution[AXE_X])
	{
		data[y * sizeline + x * bpp / 8 ] = color1;
		data[y * sizeline + x * bpp / 8 + 1] = color2;
		data[y * sizeline + x * bpp / 8 + 2] = color3;
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
