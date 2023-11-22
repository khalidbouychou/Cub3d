/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:56:14 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/22 20:28:43 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

unsigned int	cnv_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

char	**get_f_c_color(t_txtr *txtr)
{
	char	*color;
	char	**rgb;

	color = NULL;
	while (txtr)
	{
		if (!ft_strncmp(txtr->key, "F", 2) || !ft_strncmp(txtr->key, "C", 2))
		{
			color = ft_strjoin(color, txtr->value);
			color = ft_strjoin(color, ",");
		}
		txtr = txtr->next;
	}
	rgb = ft_split(color, ',');
	free(color);
	return (rgb);
}
