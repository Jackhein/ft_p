/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdelelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:10:19 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/07 18:14:05 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_tabdelelem(char **tab, int i)
{
	int		k;

	k = 0;
	while (tab && tab[k])
		k++;
	if (k < i || i < 0 || !tab)
		return ;
	k = i;
	while (tab[++k])
	{
		ft_memdel((void **)&tab[i]);
		tab[i] = ft_strdup(tab[k]);
		i++;
	}
	tab[i] = NULL;
}
