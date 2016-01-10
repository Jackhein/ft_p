/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 03:50:24 by tbalea            #+#    #+#             */
/*   Updated: 2015/06/01 04:09:43 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_i(int i)
{
	int	n;

	n = 0;
	while (i != 0 && ++n)
		i /= 10;
	return (n);
}

static char	*val_min(void)
{
	char	*str;

	if ((str = ft_strnew(11)) == NULL)
		return (NULL);
	str = "-2147483648";
	return (str);
}

char		*ft_itoa(int i)
{
	char	*str;
	int		neg;
	int		len;

	neg = 0;
	if (i < 0)
		neg = 1;
	len = len_i(i);
	if (i == -2147483648)
		return (str = val_min());
	if ((str = ft_strnew(len + neg)) == NULL)
		return (NULL);
	if (neg)
		str[0] = '-';
	str[len + neg] = '\0';
	while (i != 0)
	{
		str[--len + neg] = i % 10 + '0';
		i /= 10;
	}
	return (str);
}
