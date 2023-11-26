/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:41:00 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/26 00:50:22 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub.h"

void	free_m(t_data *m)
{
	free_2d(m->ff);
	free_2d(m->cc);
	free_2d(m->ture2d);
	free_2d(m->sq_map);
}

int	parsing(int ac, char **av, t_data *m, t_txtr *l_ture)
{
	t_mlx	*smlx;
	int		count;

	smlx = malloc(sizeof(t_mlx));
	l_ture = malloc(sizeof(t_txtr));
	if (ac != 2 || !checkextension(av[1]))
		return (free(smlx), free(l_ture),
			write(1, "Error\ninvalid args\n", 20), 0);
	count = 0;
	if (!read_map(av[1], m, &count))
		return (free(smlx), free(l_ture), 0);
	if (!valid_map(m) || !l_ture)
		return (free_2d(m->sq_map), free_2d(m->map2d),
			free_2d(m->ture2d), free(l_ture), free(smlx), 0);
	if (!lst_ture(m, &l_ture))
		return (0);
	if (!color_ture(m, l_ture))
		return (free_2d(m->sq_map), free_2d(m->ture2d),
			freelist(&l_ture), free(l_ture), free(smlx), 0);
	free_m(m);
	freelist(&l_ture);
	free(smlx);
	return (1);
}

int	color_ture(t_data *m, t_txtr *l_ture)
{
	t_txtr	*tmp;

	tmp = l_ture;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "F", 1) || !ft_strncmp(tmp->key, "C", 1))
		{
			if (!ft_process_rgb_color(tmp, m))
			{
				write(1, "Error\ninvalid RGBA color\n", 26);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
