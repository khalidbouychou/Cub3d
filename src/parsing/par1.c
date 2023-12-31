/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:16:33 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/26 13:09:34 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub.h"

int	valid_map(t_data *m)
{
	int	i;
	int	maxlen;

	maxlen = getsize_largline(m->map2d);
	i = 0;
	m->sq_map = malloc(sizeof(char *) * (getsizemap(m->map2d) + 1));
	if (!m->sq_map)
		return (0);
	while (m->map2d[i])
	{
		if (maxlen == ft_strlen(m->map2d[i]))
			m->sq_map[i] = ft_strdup(m->map2d[i]);
		else
			m->sq_map[i] = fixline(m->map2d[i], maxlen);
		i++;
	}
	m->sq_map[i] = NULL;
	m->h_map = getsizemap(m->sq_map);
	m->w_map = ft_strlen(m->sq_map[0]);
	if (!h_map(m->sq_map) || !v_map(m->sq_map))
		return (0);
	return (1);
}

void	get_x_y_player(t_mlx *smlx, t_data *m)
{
	int	i;
	int	j;

	i = 0;
	while (m->sq_map[i])
	{
		j = 0;
		while (m->sq_map[i][j])
		{
			if (m->sq_map[i][j] == 'N' || m->sq_map[i][j] == 'S'
				|| m->sq_map[i][j] == 'W' || m->sq_map[i][j] == 'E')
			{
				smlx->m->p_x = j * P_SIZE;
				smlx->m->p_y = i * P_SIZE;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	free_2d(char **m)
{
	int	i;

	i = 0;
	while (m[i])
		free(m[i++]);
	free(m);
}

void	free1(t_data *m, t_txtr *l_ture)
{
	free_2d(m->sq_map);
	free_2d(m->map2d);
	free_2d(m->ture2d);
	free(l_ture);
}

int	checkextension(char *fname)
{
	char	*dotp;

	dotp = ft_strrchr(fname, '.');
	if (dotp && !ft_strncmp(dotp, ".cub", 4))
		return (1);
	else if (!fname || !dotp)
		return (0);
	return (0);
}
