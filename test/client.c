/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 16:54:12 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/24 19:27:41 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include <stdio.h>
#include <signal.h>

//	To Do :
//	-Fork
//	-Norme
//	-Do Get/Put
//	-Archivaze

static int	state(char **rc)
{
	if (*rc == NULL || ft_strcmp("quit", *rc) != 0)
	{
		ft_resizestr(rc, ft_strlen(*rc), 1024);
		ft_putstr("\n~nipaa~ ");
		return (1);
	}
	ft_resizestr(rc, ft_strlen(*rc), -1);
	ft_putendl("\nGoodbye.");
	return (0);
}

static int	client_send(int sock)
{
	int		n;
	char	*buf;

	while (get_next_line(0, &buf) >= 0 && ((buf = ft_strdelvoid(buf)) || !buf)
			 && ((n = client_cmd(buf, sock)) >= 0)
			&& send(sock, ft_itoa((n = ft_strlen(buf))), 1024, 0) >= 0
			&& send(sock, buf, ft_strlen(buf), 0) >= 0) 
//{ft_putendl("send");
		ft_memdel((void **)&buf);
//ft_putendl("testo");}
	return (client_error(-4, sock));
}

static int	client_recv(int sock)
{
	char	*rc;
//	int		n;

	rc = NULL;
	while (state(&rc) != 0)
	{
//ft_putendl("recv");
		if (recv(sock, rc, 1024, 0) < 0)
			return (client_error(-5, sock));
		if (ft_strncmp("put", rc, 3) == 0)
			transfer_get(sock, rc);
		else
			ft_putstr(rc);
//		ft_resizestr(&rc, 1024, 1024);
	}
	return (1);
}

int			main(int argv, char** argc)
{
//	char	*buff;
//	char	*child_pid;
//	char	*rc;
	int		sock;
//	int		n;
	int		child;
//	int		pipefd[2];
	int		ret;

//	rc = NULL;
//	child_pid = NULL;
	ret = 1;
	if (argv != 3)
		return (client_error(-1, 0));
	if ((sock = client_create(argc[1], argc[2])) < 0)
		return (sock);
//	<==>--<==>--<==>
//	fork recv & send
//	<==>--<==>--<==>
//	if (pipe(pipefd) < 0)
//		return (client_error(-5, sock));
	else if ((child = fork()) < 0)
		return (client_error(-6, sock));
	else if (child == 0)
	{
//		if ((read(pipefd[1], child_pid, 1024)) == -1)
//			ft_putendl("testo");
//		ft_putendl(child_pid);
//		child = ft_atoi(child_pid);
//		close(pipefd[1]);
		ret = client_recv(sock);
		kill(0/*ft_atoi(child_pid)*/, SIGTERM);
	}
	else
	{
//		write(pipefd[0], ft_itoa(child), ft_strlen(ft_itoa(child)));
//		close(pipefd[0]);
		ret = client_send(sock);
		kill(0, SIGTERM);
	}
	return (ret);
}
//	<==>--<==>--<==>
//	fork recv & send <= without
//	<==>--<==>--<==>
/*	while (state(&rc))
	{
		if (get_next_line(0, &buff) < 0)
			return (client_error(-4, sock));
//		ft_putendl("testo-0");
		if (((n = client_cmd((buff = ft_strdelvoid(buff)), sock)) < 0)
				|| (n == 0
				&& (send(sock, ft_itoa((n = ft_strlen(buff))), 1024, 0) < 0
				|| send(sock, buff, ft_strlen(buff), 0) < 0)))
			return (client_error(-4, sock));
//		ft_putendl("testo-1");
		if ((n = client_rcv(sock, &rc)) == -1)
			return (client_error(-5, sock));
//		ft_putendl("testo-2");
//	<==>--<==>--<==>
//	recv in one time
//	<==>--<==>--<==>
	}
	return (1);
}*/


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
