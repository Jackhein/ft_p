/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 15:03:27 by tbalea            #+#    #+#             */
/*   Updated: 2015/05/28 15:07:13 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int i, size_t n)
{
	unsigned char		c;
	const unsigned char	*tmp;

	tmp = str;
	c = i;
	while (n)
	{
		if (*tmp == c)
			return ((void *)tmp);
		tmp++;
		n--;
	}
	return (NULL);
}
