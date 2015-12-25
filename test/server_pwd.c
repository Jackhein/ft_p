/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 17:18:58 by tbalea            #+#    #+#             */
/*   Updated: 2015/06/13 15:31:50 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char		*server_pwd(char *buff, char *org)
{
	int		i;
	int		j;
	char	*tmp;

	j = 1;
	tmp = getcwd(NULL, 0);
	ft_putendl(tmp);
	i = ft_strlen(org);
	ft_bzero(buff, ft_strlen(buff));
	buff[0] = '~';
	while (tmp[i] != '\0')
	{
		buff[j] = tmp[i];
		i++;
		j++;
	}
	buff[j] = '\0';
	free(tmp);
	return (buff);
}
