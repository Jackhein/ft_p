/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 16:54:12 by tbalea            #+#    #+#             */
/*   Updated: 2015/12/25 14:09:50 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include <stdio.h>

//	To Do :
//	-Fork
//	-Norme
//	-Do Get/Put

static void	fill_rc(char **rc, size_t size)
{
	*rc = (char *)malloc(size * sizeof(char));
	ft_bzero(*rc, size);
}

static void	empty_rc(char **rc, int size)
{
	ft_bzero(*rc, size);
	free(*rc);
}

static int	state(char **rc)
{
	if (*rc == NULL || ft_strcmp("quit", *rc) != 0)
	{
		empty_rc(rc, ft_strlen(*rc));
		fill_rc(rc, 1024);
		ft_putstr("~nipaa~ ");
		return (1);
	}
	empty_rc(rc, ft_strlen(*rc));
	ft_putendl("Goodbye.");
	return (0);
}

int			main(int argv, char** argc)
{
	char	*buff;
	char	*rc;
	int		sock;
	int		n;
	int		child;

	rc = NULL;
	if (argv != 3)
		return (client_error(-1, 0));
	if ((sock = create_client(argc[1], argc[2])) < 0)
		return (sock);
//	<==>--<==>--<==>
	if ((child = fork()) < 0)
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
			empty_rc(&rc, 1024);
			fill_rc(&rc, 1024);
		}
	}
	return (1);
}
/* <==>--<==>--<==>
	while (state(&rc))
	{
		if (get_next_line(0, &buff) < 0
				|| send(sock, ft_itoa((n = ft_strlen(buff))), 1024, 0) < 0
				|| send(sock, buff, ft_strlen(buff), 0) < 0)
			return (client_error(-4, sock));
		empty_rc(&rc, 1024);
		fill_rc(&rc, 1024);
		while ((n = recv(sock, rc, 1024, 0)) != 0)
		{
			if (n < 0)
				return (client_error(-5, sock));
			if (n < 1024)
				break ;
			ft_putstr(rc);
//			ft_putstr("[");
//			ft_putstr(ft_itoa(n));
//			ft_putendl("]");
			empty_rc(&rc, 1024);
			fill_rc(&rc, 1024);
		}
		ft_putendl(rc);
//		n = ft_atoi(rc);
//		empty_rc(&rc, 1024);
//		fill_rc(&rc, n);
//		if ((n = recv(sock, rc, n, 0) < 0))
//			return (client_error(-5, sock));
//		ft_putendl(rc);
	}
	return (1);
}
	<==>--<==>--<==>
*/
/*		if ((recv(sock, rc, 1024, 0) < 0))
			return (client_error(-5, sock));
		ft_putendl(rc);
		n = ft_atoi(rc);
		empty_rc(&rc, 1024);
		fill_rc(&rc, n);
		if ((n = recv(sock, rc, n, 0) < 0))
			return (client_error(-5, sock));
		ft_putendl(rc);
	}
	return (1);
}*/
