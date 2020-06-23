/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:06:58 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/23 23:37:34 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exitred(t_graph *gr, int flag)
{
	t_map *map;
	size_t	i;

	i = 0;
	while (i < NB_TEXTURE)
	{
		if (gr->text.img[i] != NULL)
			mlx_destroy_image(gr->win.mlx_ptr, gr->text.img[i]);
		i++;
	}
	map = get_map(NULL);
	free(gr->sp.pos);
	free(gr->sp.raybuff);
	ft_free(map, NULL);
	if (gr->win.img_ptr != NULL)
		mlx_destroy_image(gr->win.mlx_ptr, gr->win.img_ptr);
	if (map->utils.save_mode == FALSE)
	{
		mlx_clear_window(gr->win.mlx_ptr, gr->win.win_ptr);
		if (gr->win.win_ptr != NULL)
			mlx_destroy_window(gr->win.mlx_ptr, gr->win.win_ptr);
	}
	free(gr->win.mlx_ptr);
	exit(flag);
}

/*
**
**	appeler free_xvar((t_xvar *)gr->win.mlx_ptr)
**			a la place de free(gr->win.mlx_ptr)
**
**	void	free_xvar(t_xvar *xvar)
**	{
**		if (xvar != NULL)
**		{
**			if (xvar->private_cmap)
**				XFreeColormap(xvar->display, (Colormap)xvar->private_cmap);
**			XCloseDisplay(xvar->display);
**			free(xvar);
**		}
**	}
*/

