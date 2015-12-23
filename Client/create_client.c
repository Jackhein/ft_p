/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/24 15:55:34 by tbalea            #+#    #+#             */
/*   Updated: 2015/05/24 15:56:19 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(addr);
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(in)) == -1)
	{
		ft_putendl("Connection fail");
		exit(0);
	}
	return (sock);
}
