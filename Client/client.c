/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 16:54:12 by tbalea            #+#    #+#             */
/*   Updated: 2015/05/24 15:56:30 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	main(int argv, char* argc)
{
	int	port;
	int	sock;

	if (argv != 3)
	{
		ft_putendl("Usage: Client <addr> <port>");
		return (-1);
	}
	port = ft_atoi(av[2]);
	discuss((sock = create_client(av[1], port)));
	close(sock);
	return (0);
}
