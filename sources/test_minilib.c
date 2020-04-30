/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 14:39:03 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 22:30:02 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		deal_key(int key, void *param)
{
	ft_putchar_fd('X', 1);
	(void)key;
	(void)param;
	return (SUCCESS);
}

void	test_minilib(t_state_machine *machine)
{
	int   bpp;
	int   endian;
	int   x;
	int   y;
	int	size_line;
	t_graphic	graphic;

	ft_bzero(&graphic, sizeof(graphic));
	x = 0;
	y = 0;
	graphic.indic.color_total = machine->info.tab_color_f[R]
								+ (machine->info.tab_color_f[G] << 8)
								+ (machine->info.tab_color_f[B] << 16);
	graphic.indic.mlx_ptr = mlx_init();
	graphic.indic.img_ptr = mlx_new_image(graphic.indic.mlx_ptr,
										machine->info.str_resolution[AXE_X],
										machine->info.str_resolution[AXE_Y]);
	graphic.indic.data = mlx_get_data_addr(graphic.indic.img_ptr, &bpp,
												&size_line, &endian);
	graphic.indic.img_color = mlx_get_color_value(graphic.indic.mlx_ptr,
													graphic.indic.color_total);
	graphic.indic.color1 = machine->info.tab_color_f[B];
	graphic.indic.color2 = machine->info.tab_color_f[G];
	graphic.indic.color3 = machine->info.tab_color_f[R];
	while (x < machine->info.str_resolution[AXE_X])
	{
		graphic.indic.data[y * size_line + x * bpp / 8 ]
								= graphic.indic.color1;
		graphic.indic.data[y * size_line + x * bpp / 8 + 1]
								= graphic.indic.color2;
		graphic.indic.data[y * size_line + x * bpp / 8 + 2]
								= graphic.indic.color3;
		x++;
		if (x == machine->info.str_resolution[AXE_X] &&
				y < machine->info.str_resolution[AXE_Y])
		{
			x = 0;
			y++;
		}
	}
	graphic.indic.win_ptr = mlx_new_window(graphic.indic.mlx_ptr,
								machine->info.str_resolution[AXE_X],
								machine->info.str_resolution[AXE_Y],
								"NOM A CHANGER");
	mlx_put_image_to_window(graphic.indic.mlx_ptr, graphic.indic.win_ptr,
								graphic.indic.img_ptr, 0, 0);
	while (42)
	{
	}
}
