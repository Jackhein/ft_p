/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/24 16:12:34 by tbalea            #+#    #+#             */
/*   Updated: 2015/06/01 02:17:34 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "ft_p.h"

typedef struct	s_client
{
	struct sockaddr_in	sin;
	unsigned int		len;
	int					sck;
	int					cpi;
}				t_client;

int		create_server(int port);
int		server_error(int type);
char	*server_cmd(char *buff, char *org, int socket);
char	*server_cd(char *buff, char *org);
char	*server_ls(char *buff, int sock);
char	*server_pwd(char *buff, char *org);

#endif
