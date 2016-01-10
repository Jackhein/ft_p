/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/24 15:55:34 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/08 16:26:16 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	client_create(char *addr, char *port)
{
	int					sock;
	struct addrinfo		info;
	struct addrinfo		*res;

	ft_memset(&info, 0, sizeof(info));
	info.ai_family = PF_INET;
	info.ai_socktype = SOCK_STREAM;
	info.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(addr, port, &info, &res) != 0)
	{
		free(res);
		return (client_error(-2, 0));
	}
	sock = socket(info.ai_family, info.ai_socktype, info.ai_protocol);
	if (connect(sock, res->ai_addr, res->ai_addrlen) < 0)
	{
		free(res);
		return (client_error(-3, sock));
	}
	free(res);
	return (sock);
}
