/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 16:54:12 by tbalea            #+#    #+#             */
/*   Updated: 2015/12/30 22:58:45 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include <stdio.h>

//	To Do :
//	-Fork
//	-Norme
//	-Do Get/Put
//	-Archivaze

static int	state(char **rc)
{
	if (*rc == NULL
			|| ft_strcmp("quit", *rc) != 0
			|| ft_strcmp("exit", *rc) != 0)
	{
		ft_resizestr(rc, ft_strlen(*rc), 1024);
		ft_putstr("~nipaa~ ");
		return (1);
	}
	ft_resizestr(rc, ft_strlen(*rc), -1);
	ft_putendl("Goodbye.");
	return (0);
}

int			main(int argv, char** argc)
{
	char	*buff;
	char	*rc;
	int		sock;
	int		n;
//	int		child;

	rc = NULL;
	if (argv != 3)
		return (client_error(-1, 0));
	if ((sock = create_client(argc[1], argc[2])) < 0)
		return (sock);
//	<==>--<==>--<==>
//	fork recv & send
//	<==>--<==>--<==>
	while (state(&rc))
	{
		if (get_next_line(0, &buff) < 0)
			return (client_error(-4, sock));
		if (((n = client_spec_cmd((buff = ft_strdelvoid(buff)), sock)) < 0)
				|| (n == 0
				&& (send(sock, ft_itoa((n = ft_strlen(buff))), 1024, 0) < 0
				|| send(sock, buff, ft_strlen(buff), 0) < 0)))
			return (client_error(-4, sock));
		if ((n = client_rcv(sock, &rc)) == -1)
			return (client_error(-5, sock));
//	<==>--<==>--<==>
//	recv in one time
//	<==>--<==>--<==>
	}
	return (1);
}
//	<==>--<==>--<==>
//	fork recv & send
//	<==>--<==>--<==>
/*	if ((child = fork()) < 0)
		return (child);
	if (child == 0)
	{
		while (get_next_line(0, &buff) > 0
				&& send(sock, ft_itoa((n = ft_strlen(buff))), 1024, 0) >= 0
				&& send(sock, buff, ft_strlen(buff), 0) >= 0)
			;
		return (client_error(-4, sock));
	}
	else
	{
		while ((n = recv(sock, rc, 1024, 0)) != 0)
		{
			if (n < 0)
				return (client_error(-5, sock));
			if (n < 1024)
				state(&rc) ;
			ft_putstr(rc);
			resize_rc(&rc, 1024, 1024);
		}
	}
	return (1);
}*/

//	<==>--<==>--<==>
//	recv in one time
//	<==>--<==>--<==>
/*		if ((recv(sock, rc, 1024, 0) < 0))
			return (client_error(-5, sock));
		ft_putendl(rc);
		n = ft_atoi(rc);
		resize_rc(&rc, 1024, n);
		if ((n = recv(sock, rc, n, 0) < 0))
			return (client_error(-5, sock));
		ft_putendl(rc);
	}
	return (1);
}*/
