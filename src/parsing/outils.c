/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:38:41 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/26 00:54:38 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub.h"

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned int	i;
	char			*p_dest;
	char			*p_src;

	if (dest == NULL && src == NULL)
		return (0);
	p_dest = (char *)dest;
	p_src = (char *)src;
	i = -1;
	while (++i < n)
		p_dest[i] = p_src[i];
	return (p_dest);
}

char	*ft_strdup(char *s1)
{
	char			*tmp;
	unsigned int	size;

	size = ft_strlen(s1);
	tmp = (char *)malloc(size + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, s1, size);
	tmp[size] = '\0';
	return (tmp);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	checkcolorvalues(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_process_rgb_color(t_txtr *tmp, t_data *m)
{
	char	**rgb;

	rgb = ft_split(tmp->value, ',');
	if (!checkcolorvalues(rgb))
		return (free_2d(rgb), 0);
	if (!ft_strncmp(tmp->key, "F", 2))
		m->ff = ft_split(tmp->value, ',');
	else if (!ft_strncmp(tmp->key, "C", 2))
		m->cc = ft_split(tmp->value, ',');
	free_2d(rgb);
	return (1);
}
