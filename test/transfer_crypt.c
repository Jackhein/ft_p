/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_crypt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 20:48:43 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/14 21:22:58 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*crypting(char *txt)
{
	char	*crypt;
	int		len;
	int		i;

	len = 0;
	while (txt[len])
		len++;
	crypt = (char *)malloc((len * 2 + 1) * sizeof(char));
	i = 0;
	while (i < len)
	{
		crypt[i * 2] = 'a' + ((txt[i] >> 4) & 15);
		crypt[i * 2 + 1] = 'a' + ((txt[i] >> 4) & 15);
		i++;
	}
	crypt[len * 2] = '\0';
	return (crypt);
}

char	*decrypting(char *crypt)
{
	char	*txt;
	int		len;
	int		i;

	len = 0;
	while (crypt[len])
		len++;
	len = len / 2;
	txt = (char *)malloc(((len) + 1) * sizeof(char));
	i = 0;
	while (i < len)
	{
		txt[i] = ((crypt[i * 2] - 'a') << 4) + (crypt[(i * 2) + 1] - 'a');
		i++;
	}
	txt[i] = '\0';
	return (txt);
}
