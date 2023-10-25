/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:38:41 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/25 19:50:35 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	char	*p_dest;
	char	*p_src;
	unsigned int	i;

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
	char	*tmp;
	unsigned int	size;

	size = ft_strlen(s1);
	tmp = (char *)malloc(size + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, s1, size);
	tmp[size] = '\0';
	return (tmp);
}

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
