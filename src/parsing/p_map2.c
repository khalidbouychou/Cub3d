/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:59:11 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/22 22:59:55 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub.h"

char	*getlastline(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (map[i - 1]);
}

int	check_first_last_line(char **map)
{
	if (!check_l_surroundedbyone(map[0])
		|| !check_l_surroundedbyone(getlastline(map)))
	{
		write(1, "Error\n(first/last) line not surrounded by 1 \n", 46);
		return (0);
	}
	return (1);
}

int	check_countture(t_map *m, int count)
{
	if (count < 6 || count > 6)
	{
		write(1, "Error\ninvalid map element [texture/color]\n", 41);
		free(m->ture);
		free(m->line);
		return (0);
	}
	return (1);
}
