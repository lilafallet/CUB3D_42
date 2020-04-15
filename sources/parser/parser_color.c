/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 10:36:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/15 16:20:01 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

int	is_color(t_vector *vct, char **tab_color)
{
	int	index;
	char	*str;

	index = 0;
	str = NULL;
	while (index < NB_INDIC_COLOR)
	{
		str = ft_strnstr(vct_getstr(vct), tab_color[index], vct_getlen(vct));
		if (str != NULL)
			break ;
		index++; /*recup index qui va determiner si il s'agit de F ou de G*/
	}
	ft_printf("IS_COLOR -> index = %d\n", index); //
	return (index);
}

static int	verif_before(t_vector *vct, size_t clen)
{
	size_t	i;
	char	*str;
	int		ret;

	i = 0;
	str = vct_getstr(vct);
	ret = TRUE;
	while (i < clen)
	{
		if (str[i] != SPACE && str[i] != TAB)
			ret = ERROR;
		i++;
	}
	return (ret);
}

static int	error_or_true(t_vector *color, size_t count_loops)
{
	int				ret;

	printf("SPLIT_COLOR -> count_loops = %zu\n", count_loops); //
	ret = TRUE;
	if ((count_loops == 0 || count_loops == 6) &&
			vct_apply(color, IS_WHITESPACE) == FALSE)
		ret = ERROR;
	else if (count_loops == 1 && vct_apply(color, IS_DIGIT) == FALSE)
		ret = ERROR;
	else if ((count_loops == 2 || count_loops == 4) && vct_apply(color,
				IS_WHITESPACECOMA) == FALSE)
		ret = ERROR;
	else if ((count_loops == 3 || count_loops == 5) && vct_apply(color,
				IS_WHITESPACEDIGIT) == FALSE)
		ret = ERROR;
	count_loops++;
	return (ret);
}

static int	split_color(t_vector *vct, char *str)
{
	int	ret;
	t_vector	*color;
	t_vector	*cpy_vct;
	size_t		count_num;
	size_t		count_loops;

	color = vct_new();
	cpy_vct = vct_new();
	vct_addstr(cpy_vct, str);
	ret = TRUE;
	count_num = 0;
	count_loops = 0;
	while ((color = vct_split(cpy_vct, ", \t", ALL_SEP)) != NULL) /*remplacer avec TAB ET SPACE*/
	{
		ret = error_or_true(color, count_loops);
		ft_printf("SPLIT_COLOR -> color->str = %s\n", vct_getstr(color));
		if (ret == ERROR)
			break ;
		count_loops++;
		vct_del(&color);
	}
	vct_del(&cpy_vct);
	return (ret);
}

int	pre_split_color(t_vector *vct, char *str)
{
	size_t	clen;
	int		ret;
	char	*str_clen;

	ret = TRUE; //
	str_clen = NULL;
	clen = vct_clen(vct, str[0]);
	printf("SPLIT_COLOR -> clen = %zu\n", clen); //
	ret = verif_before(vct, clen); /*verif si char indesirable avant indic*/
	if (ret == TRUE)
	{
		str_clen = vct_getstr(vct); /*ajoute vct->str a str_clen*/
		str_clen = ft_strdup(str_clen + clen + 1); /*str_clen= str apres indic*/
		ft_printf("SPLIT_COLOR -> str_clen = %s\n", str_clen); //
		ret = split_color(vct, str_clen);
	}
	free(str_clen);
	return (ret);
}
