/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 16:23:15 by tbalea            #+#    #+#             */
/*   Updated: 2015/05/31 16:26:54 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_newstr(char *old, char *txt)
{
	int	i;

	i = -1;
	ft_memdel(&old);
	old = ft_memalloc(ft_strlen(txt));
	while (txt[++i] != '\0')
		old[i] = txt[i];
	old[i] = txt[i];
}
