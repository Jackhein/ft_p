/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 22:13:48 by tbalea            #+#    #+#             */
/*   Updated: 2015/12/25 09:02:11 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	is_empty(char c)
{
	if (c == '\0' || c == '\t' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

char		*server_cmd(char *buff, char *org, int socket)
{
	if (buff == NULL)
		return ("Wat ?");
	else if (ft_strncmp("ls", buff, 2) == 0 && is_empty(buff[2]))
		return (server_ls(buff, socket));
	else if (ft_strncmp("cd", buff, 2) == 0 && is_empty(buff[2]))
		return (server_cd(buff, org));
//	else if (ft_strncmp("get", buff, 3) == 0 && is_empty(buff[3]))
//		return (server_get(buff, org, socket));
//	else if (ft_strncmp("put", buff, 3) == 0 && is_empty(buff[3]))
//		;
	else if (ft_strncmp("pwd", buff, 3) == 0 && is_empty(buff[3]))
		return (server_pwd(buff, org));
	else if (ft_strncmp("quit", buff, 4) == 0 && is_empty(buff[4]))
		return ("quit");
	return ("Wat ?");
}
