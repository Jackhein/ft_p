/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 22:13:48 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/25 04:00:37 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*put_and_mput(char *buff, int socket)
{
	char	**tab;
	char	*put;
	int		multi;
	int		i;
	int		putok;

	i = 0;
	tab = ft_strsplit(buff, ' ');
	multi = (ft_strncmp("mput", buff, 4) == 0) ? 1 : 0;
	ft_resizestr(&buff, 1024, 1024);
	while (tab[++i] && (multi || i < 2))
	{
		put = ft_strjoin("get ", tab[i]);
		if (send(socket, put, ft_strlen(put), 0) < 0
				|| recv(socket, buff, 1024, 0) < 0)
			return ("Transfer put error");
		putok = transfer_get(socket, buff);
		if (send(socket, (putok > 0) ? "Get Ook." : "Get Not Ook.",\
					putok ? 8 : 12 , 0) < 0)
			return ("Transfer put error");
	}
	return (multi ? "mput done" : "put done");
}

static char	*mget(char *buff, int socket)
{
	char	**tab;
	char	*arg;
	int		i;
	int		e;

	i = 0;
	tab = ft_strsplit(buff, ' ');
	while (tab[++i])
	{
		arg = ft_strjoin("put ", tab[i]);
		e = transfer_put(socket, arg);
		if ((e = send(socket, e ? "Ook" : "Not Ook", e ? 4 : 8, 0)) < 0)
			return (NULL);
	}
	return ("mget Ook.");
}

char		*server_cmd(char *buff, char *org, int socket)
{
//ft_putstr("test|");
//ft_putstr(buff);
//ft_putendl("|test");
//ft_putendl("popi");
//ft_putendl(org);
	if (buff == NULL)
		return ("Wat ?");
	else if (ft_strncmp("ls", buff, 2) == 0 && ft_isempty(buff[2]))
		return (server_ls(buff, org, socket));
	else if (ft_strncmp("cd", buff, 2) == 0 && ft_isempty(buff[2]))
		return (server_cd(buff, org));
	else if (ft_strncmp("get", buff, 3) == 0 && ft_isempty(buff[3]))
	{
		buff[0] = 'p';
		buff[1] = 'u';
//ft_putendl(">get<");
//ft_putendl(buff);
//		if (recv(socket, buff, 1024, 0) < 0)
//			return ("Wat ?");
//ft_putendl(">get<");
		return (transfer_put(socket, buff) ? "Put Ook." : "Put Not Ook.");
	}
//{ft_putendl("SRV_PUT");
	else if ((ft_strncmp("mput", buff, 4) == 0 && ft_isempty(buff[4]))
			|| (ft_strncmp("put", buff, 3) == 0 && ft_isempty(buff[3])))
		return (put_and_mput(buff, socket));//transfer_get(socket, buff) ? "Get Ook." : "Get Not Ook.");
//}
	else if (ft_strncmp("pwd", buff, 3) == 0 && ft_isempty(buff[3]))
		return (server_pwd(buff, org));
	else if ((ft_strncmp("quit", buff, 4) == 0
			|| ft_strncmp("exit", buff, 4) == 0) && ft_isempty(buff[4]))
		return ("quit");
	else if (ft_strncmp("end put", buff, 7) == 0 && ft_isempty(buff[7]))
		return ("");
	else if (ft_strncmp("mget", buff, 4) == 0 && ft_isempty(buff[4]))
		return (mget(buff, socket));
//ft_putendl("END SRV_CMD");
	return ("Wat ?");
}
