/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/24 16:25:38 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/08 16:51:09 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int server_create(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
//	struct sockaddr_in6	sin6;

	if ((proto = getprotobyname("tcp")) == 0)
		return (server_error(-2));
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
//	sin6.sin6_addr.s6_addr = htonl(INADDR_ANY);
//	sin6.sin6_family = AF_INET6;
//	sin6.sin6_port = htons(port);
//	inet_pton(AF_INET6, "2001:720:1500:1::a100", &(sin6.sin6_addr));
//ft_putendl("adr");
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
		return (server_error(-3));
//ft_putendl("bid");
	if (listen(sock, 17) < 0)
		return (server_error(-4));
//ft_putendl("lst");
	return (sock);
}
