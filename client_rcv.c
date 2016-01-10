/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_rcv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 21:22:04 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/03 14:46:24 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int			client_rcv(int sock, char **rc)
{
	int	n;

	ft_resizestr(rc, 1024, 1024);
//	ft_putendl("testo-1-0");
	while ((n = recv(sock, *rc, 1024, 0)) != 0)
	{
//		ft_putendl("testo-1-1");
		if (n < 0)
			return (-1);
		if (n < 1024)
			break ;
		ft_putstr(*rc);
		ft_resizestr(rc, 1024, 1024);
	}
//	ft_putendl("testo-1-2");
	ft_putendl(*rc);
//	ft_putendl("testo-1-3");
	return (1);
}
