/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/24 16:11:31 by tbalea            #+#    #+#             */
/*   Updated: 2015/12/25 14:09:58 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "server.h"

//	To Do:
//	-Fork client
//	-Norme
//	-Test ls
//	-Do Put/Get

//	What are the client doing
static void	cmd_client(int cs, char *sd)
{
	ft_putstr(ft_itoa(cs));
	ft_putstr(" : ");
	ft_putendl(sd);
}

//	Reset the message to send/receiv
static char	*reset_msg(char *msg, int old_size, int new_size)
{
	if (old_size > 0)
	{
		ft_bzero(msg, old_size);
		free(msg);
	}
	if (old_size > 0)
	{
		msg = (char *)malloc((new_size + 1) * sizeof(char));
		ft_bzero(msg, new_size);
		return (msg);
	}
	return (NULL);
}

//	Close client connection
static int	end_sock(int socket, char *pwd, char *recv, int type)
{
	ft_bzero(pwd, ft_strlen(pwd));
	free(pwd);
	if (recv != NULL)
	{
		ft_bzero(recv, ft_strlen(recv));
		free(recv);
	}
	close(socket);
	if (type < 0)
		return (server_error(type));
	return (type);
}

static int	client(int cs)
{
	int		n;
	char	*msg;
	char	*pwd;
	int		child;

	cmd_client(cs, "connected");
	pwd = getcwd(NULL, 0);
//	<==>--<==>--<==>
	if ((child = fork()) < 0)
		return (end_sock(cs, pwd, NULL, -7));
	if (child == 0)
	{
		msg = reset_msg(NULL, 0, 1024);//First rep
		while (send(cs, ft_itoa(ft_strlen(msg)), 1024, MSG_DONTWAIT) >= 0 &&
				send(cs, msg, ft_strlen(msg), MSG_DONTWAIT) >= 0)
			;//2nd rep
		return (end_sock(cs, pwd, msg, -6));
	}
	else
	{
		msg = reset_msg(NULL, 0, 1024);
		while (recv(cs, msg, 1024, 0) >= 0)
		{
			msg = reset_msg(msg, 1024, (n = ft_atoi(msg)));
			if (recv(cs, msg, n, 0) < 0)
				break ;
			server_cmd(msg, pwd, cs);//	Send to child 0;
			if (ft_strcmp("quit", msg) == 0)
				return (end_sock(cs, pwd, msg, 1));
			msg = reset_msg(msg, n, 1024);
		}
		return (end_sock(cs, pwd, msg, -5));
	}
}
/*	<==>--<==>--<==>
	while (42)
	{
		rc = (char *)ft_memalloc(1024);
		if (recv(cs, rc, 1024, 0) < 0)
			return (end_sock(cs, pwd, rc, -5));
		n = ft_atoi(rc);
		ft_bzero(rc, ft_strlen(rc));
		free(rc);
		rc = (char *)ft_memalloc(n);
		if (n != 0 && (n = recv(cs, rc, n, 0)) < 0)
			return (end_sock(cs, pwd, rc, -5));
//		ft_putendl(rc);
		sd = server_cmd(rc, pwd, cs);
		ft_putendl("before send");
		ft_putendl(sd);
		cmd_client(cs, sd);
		if (send(cs, ft_itoa(ft_strlen(sd)), 1024, MSG_DONTWAIT) < 0 ||
			send(cs, sd, ft_strlen(sd), MSG_DONTWAIT) < 0)
			return (end_sock(cs, pwd, rc, -6));
		if (ft_strcmp("quit", sd) == 0)
			return (end_sock(cs, pwd, rc, 1));
	}
}
*/

int			main(int argv, char** argc)
{
	t_client			c;
	int					port;
	int					sock;
	struct sockaddr_in	from;
	int					from_size;

	from_size = sizeof from;
	if (argv != 2)
		return (server_error(-1));
	port = ft_atoi(argc[1]);
	if ((sock = create_server(port)) < 0)
		return (sock);
	while (42)
	{
		c.sck = accept(sock, (struct sockaddr *)&c.sin, &c.len);
		if ((c.cpi = fork()) < 0)
			server_error(-7);
		else if (c.cpi == 0)
			return (client(c.sck));
	}
	close(sock);
	return (0);
}
