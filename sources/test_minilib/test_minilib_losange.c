/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib_losange.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:05:51 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/06 19:39:28 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h> //

t_graph	*graph_holder(t_graph *graph)
{
	static t_graph	*graph_keep;

	if (graph_keep == NULL && graph != NULL)
		graph_keep = graph;
	return (graph_keep);
}

int			get_pos(t_coord *p)
{
	t_graph	*graph;

	graph = graph_holder(ACCESS);
	return (p->y * graph->recup.size_line + p->x * graph->recup.bits / 8);
}

static void	fill_pixels(t_coord point)
{
	t_graph	*graph;

	graph = graph_holder(ACCESS);
	graph->recup.data[get_pos(&point)] = graph->utils.r_f;
	graph->recup.data[get_pos(&point) + 1] = graph->utils.g_f;
	graph->recup.data[get_pos(&point) + 2] = graph->utils.b_f;
}

static void	init_graph(t_graph *graph, t_map *map)
{
	int	bits;
	int	endian;
	int	size_line;
	
	graph->recup.mlx_ptr = mlx_init();
	graph->recup.img_ptr = mlx_new_image(graph->recup.mlx_ptr,
											map->recup.str_resolution[AXE_X],
											map->recup.str_resolution[AXE_Y]);
	graph->utils.r_f = map->recup.tab_color_f[B];
	graph->utils.g_f = map->recup.tab_color_f[G];
	graph->utils.b_f = map->recup.tab_color_f[R];
	graph->recup.data = mlx_get_data_addr(graph->recup.img_ptr, &bits,
											&size_line, &endian);
	graph->recup.bits = bits;
	graph->recup.size_line = size_line;
	graph->recup.endian = endian;
}

void	process_window(t_graph *graph, t_map *map)
{
	graph->recup.win_ptr = mlx_new_window(graph->recup.mlx_ptr,
								map->recup.str_resolution[AXE_X],
								map->recup.str_resolution[AXE_Y],
								"NOM A CHANGER");
	mlx_put_image_to_window(graph->recup.mlx_ptr, graph->recup.win_ptr,
								graph->recup.img_ptr, graph->utils.pos_x,
								graph->utils.pos_y);
	mlx_loop(graph->recup.mlx_ptr);

}

t_coord		get_coord(int x, int y)
{
	t_coord point;

	point.x = x;
	point.y = y;
	return (point);
}

t_set_coord	get_coord_set(t_coord start, t_coord end)
{
	t_set_coord	set;

	set.start = start;
	set.end = end;
	return (set);
}


void	down(t_coord err_adjust, t_coord deg, t_coord incr, t_set_coord set)
{
	int		size;
	int		i;
	
	i = 0;
	size = err_adjust.x;
	while (i <= size) /*tant que plus petit longueur x*/
	{
		fill_pixels(set.start);
		set.start.x += incr.x;
		err_adjust.x -= deg.y;
		if (err_adjust.x < 0) /*si pixels dessous*/
		{
			set.start.y += incr.y;
			err_adjust.x += deg.x;
		}
		i++;	
	}
}

void	up(t_coord err_adjust, t_coord deg, t_coord incr, t_set_coord set)
{
	int		size;
	int		i;

	i = 0;
	size = err_adjust.y;
	while (i <= size)
	{
		fill_pixels(set.start);
		set.start.y += incr.y;
		err_adjust.y -= deg.x;
		if (err_adjust.y < 0) /*si pixel dessus*/
		{
			set.start.x += incr.x;
			err_adjust.y += deg.y;
		}
		i++;
	}
}

void	trace(t_coord start, t_coord end)
{
	t_coord		err_adjust;
	t_coord		deg;
	t_coord		incr;
	t_set_coord	set;

	set = get_coord_set(start, end);
	err_adjust = get_coord(ft_abs(set.end.x - set.start.x),
							ft_abs(set.end.y - set.start.y));
	deg = get_coord(2 * err_adjust.x, 2 * err_adjust.y);
	incr = get_coord((set.start.x >= set.end.x) ? -1 : 1,
					(set.start.y >= set.end.y) ? -1 : 1);
	if (err_adjust.x > err_adjust.y)
		down(err_adjust, deg, incr, set);
	else
		up(err_adjust, deg, incr, set);
}

void	test_minilib_losange(t_map *map)
{
	t_graph	graph;

	ft_bzero(&graph, sizeof(graph));
	graph_holder(&graph);
	init_graph(&graph, map);

	t_coord a;
	t_coord	b;
	
	a = get_coord(800, 0);
	b = get_coord(0, 800);

	while (a.x != a.y && b.x != b.y)
	{
		trace(a, b);
		a.x += (a.x < a.y) ? 1 : -1;
		b.x += (b.x < b.y) ? 1 : -1;
	}

	process_window(&graph, map);
}
