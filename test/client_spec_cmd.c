/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_spec_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 20:49:53 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/11 19:10:35 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

/*static int	client_ls(char *buff, int sock)
{
	int		n;
	char	*rc;

	if (send(sock, ft_itoa((n = ft_strlen(buff))), 1024, 0) < 0
		|| send(sock, buff, ft_strlen(buff), 0) < 0)
		return (-1);
	ft_resizestr(&rc, -1, 1024);
	if ((n = client_rcv(sock, &rc)) == -1)
		return (-1);
	ft_resizestr(&rc, 1024, -1);
	return (1);
}*/

int			client_spec_cmd(char *buf, int sock)
{
	char	**tab;
	int		r;

	r = 0;
	tab = ft_strsplit(buf, ' ');
//	if (buf == NULL)
//		r = 0;
//	else if (ft_strncmp("lls", buf, 3) == 0 && ft_isempty(buf[3]))
//		return (client_ls(buf, sock));
//	else if (ft_strncmp("lpwd", buf, 4) == 0 && ft_isempty(buf[4]))
//		return (client_pwd(buf, sock));
//	else if (ft_strncmp("lcd", buf, 3) == 0 && ft_isempty(buf[3]))
//		return (client_cd(buf, sock));
	if (ft_strncmp("put", buf, 3) == 0 && ft_isempty(buf[3]) && (r = 1)
			&& (r = send(sock, tab[0], ft_strlen(tab[0]), 0)) >= 0)
		transfer_put(tab[1], sock);
	else if (ft_strncmp("get", buf, 3) == 0 && ft_isempty(buf[3])
			&& (r = send(sock, tab[0], ft_strlen(tab[0]), 0)) >= 0
			&& (r = send(sock, tab[1], ft_strlen(tab[1]), 0)) >= 0 && (r = 1))
		transfer_get(sock);
	else if (ft_strncmp("mput", buf, 4) == 0 && ft_isempty(buf[4]) && (r = 1))
	{
		while (tab++ && (r = send(sock, "put", ft_strlen(tab[0]), 0)) >= 0)
			transfer_put(*tab, sock);
	}
	else if (ft_strncmp("mget", buf, 4) == 0 && ft_isempty(buf[4]))
	{
		while (tab++ && (r = send(sock, "get", ft_strlen("get"), 0)) >= 0
				&& (r = send(sock, *tab, ft_strlen(*tab), 0)) >= 0)
			transfer_get(sock);
	}
	ft_tabdel(tab);
	return (r);
}
