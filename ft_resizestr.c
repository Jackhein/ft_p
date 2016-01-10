/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resizestr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 21:33:54 by tbalea            #+#    #+#             */
/*   Updated: 2015/12/30 21:58:00 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_resizestr(char **str, int empty, int fill)
{
	if (empty >= 0)
	{
		ft_bzero(*str, empty);
		free(*str);
	}
	if (fill >= 0)
	{
		*str = (char *)malloc(fill * sizeof(char));
		ft_bzero(*str, fill);
	}
}
