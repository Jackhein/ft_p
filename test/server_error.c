/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 12:02:53 by tbalea            #+#    #+#             */
/*   Updated: 2015/05/28 17:46:42 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static const char* msg[] = {"Usage: ./serveur <port>", "Get protocol error",
	"Bind error", "Listen error", "Recv error", "Send error", "Fork error"};

int	server_error(int type)
{
	ft_putendl(msg[-1 * type - 1]);
	return (type);
}
