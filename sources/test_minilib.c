//mettre le header

#include "cub3d.h"

void	test_minilib(t_state_machine *machine)
{
	void	*mlx_ptr;
	void	*windows_ptr;

	ft_printf("tu rentres ici ?\n"); //
	mlx_ptr = mlx_init();
	windows_ptr = mlx_new_windows(mlx_ptr, machine->info.str_resolution[AXE_X],
									machine->info.str_resolution[AXE_Y],
									"coucou c'est moi :D");
	mlx_loop(mlx_ptr);
}
