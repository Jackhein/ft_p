/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_spec_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 20:49:53 by tbalea            #+#    #+#             */
/*   Updated: 2015/12/30 22:57:02 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int	client_ls(char *buff, int sock)
{
	int		n;
	char	*rc;

	if (send(sock, ft_itoa((n = ft_strlen(buff))), 1024, 0) < 0
		|| send(sock, buff, ft_strlen(buff), 0) < 0)
		return (-1);
	ft_resizestr(&rc, -1, 1024);
	client_rcv(sock, &rc);
	ft_resizestr(&rc, 1024, -1);
	return (1);
}

int			client_spec_cmd(char *buff, int sock)
{
	if (buff == NULL)
		return (0);
	else if (ft_strncmp("ls", buff, 2) == 0 && ft_isempty(buff[2]))
		return (client_ls(buff, sock));
	return (0);
}
