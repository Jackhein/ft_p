/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 12:02:53 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/04 20:47:26 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static const char* msg[] = {"Usage: ./client <addr> <port>",
	"Invalide host error", "Connection error", "Send error", "Recv error",
	"Pipe client error", "Fork client error"};

int	client_error(int type, int sock)
{
	if (sock)
		close(sock);
	ft_putendl(msg[-1 * type - 1]);
	return (type);
}
