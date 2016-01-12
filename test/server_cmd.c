/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 22:13:48 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/12 15:45:50 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char		*server_cmd(char *buff, char *org, int socket)
{
ft_putendl(buff);
ft_putendl("popi");
	if (buff == NULL)
		return ("Wat ?");
	else if (ft_strncmp("ls", buff, 2) == 0 && ft_isempty(buff[2]))
		return (server_ls(buff, org, socket));
	else if (ft_strncmp("cd", buff, 2) == 0 && ft_isempty(buff[2]))
		return (server_cd(buff, org));
	else if (ft_strncmp("get", buff, 3) == 0 && ft_isempty(buff[3]))
	{
ft_putendl(buff);
		if (recv(socket, buff, 1024, 0) < 0)
			return ("Wat ?");
		return (transfer_put(buff, socket) ? "Put Ook." : "Put Not Ook.");
	}
	else if (ft_strncmp("put", buff, 3) == 0 && ft_isempty(buff[3]))
		return (transfer_get(socket) ? "Get Ook." : "Get Not Ook.");
	else if (ft_strncmp("pwd", buff, 3) == 0 && ft_isempty(buff[3]))
		return (server_pwd(buff, org));
	else if ((ft_strncmp("quit", buff, 4) == 0
			|| ft_strncmp("exit", buff, 4) == 0) && ft_isempty(buff[4]))
		return ("quit");
	return ("Wat ?");
}
