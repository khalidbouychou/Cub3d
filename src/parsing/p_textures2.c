/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_textures2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:53:18 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/22 23:00:03 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub.h"

int	get_index(char *line, int i)
{
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

t_txtr	*new_texture(char *line)
{
	t_txtr	*list;

	list = (t_txtr *)malloc(sizeof(t_txtr));
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			||!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)))
	{
		list->key = ft_substr(line, 0, 2);
		list->value = ft_substr(line, get_index(line, 2), ft_strlen(line));
	}
	else if ((!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
	{
		list->key = ft_substr(line, 0, 1);
		list->value = ft_substr(line, get_index(line, 1), ft_strlen(line));
	}
	list->next = NULL;
	return (list);
}

t_txtr	*lst_back_ture(t_txtr *l_ture, t_txtr *new)
{
	t_txtr	*tmp;

	tmp = l_ture;
	if (l_ture == NULL)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (l_ture);
}

int	lst_ture(t_map *m, t_txtr **l_ture)
{
	int		i;
	t_txtr	*tmp;

	i = 0;
	*l_ture = NULL;
	while (m->ture2d[i])
	{
		tmp = new_texture(m->ture2d[i++]);
		if (!tmp)
			return (0);
		(*l_ture) = lst_back_ture((*l_ture), tmp);
		free(tmp);
	}
	return (1);
}
