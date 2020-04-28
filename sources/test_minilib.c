/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 14:39:03 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/28 15:29:45 by lfallet          ###   ########.fr       */
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
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, machine->info.str_resolution[AXE_X],
									machine->info.str_resolution[AXE_Y],
									"coucou c'est moi :D");
	(void)win_ptr;
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
}
