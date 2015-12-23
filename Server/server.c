/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/24 16:11:31 by tbalea            #+#    #+#             */
/*   Updated: 2015/05/24 18:44:36 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	main(int argv, char** argc)
{
	int					ss;
	int					port;
	int					sock;
	struct sockaddr_in	ssin;
	unsigned int		slen;

	if (argv != 2)
	{
		ft_putendl("Usage: ./serveur <port>");
		return (-1);
	}
	port = ft_atoi(argc[1]);
	sock = create_server(port);
	ss = accept(sock, (struct sockaddr *)&ssin, &slen);
	close(ss);
	close(sock);
	return (0);
}
