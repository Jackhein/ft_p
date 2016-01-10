/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 16:52:46 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/08 16:27:26 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "ft_p.h"

int	client_create(char *addr, char *port);
int	client_error(int type, int sock);
int	client_spec_cmd(char *buff, int sock);
int	client_rcv(int sock, char **rc);

#endif
