/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/24 16:50:30 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/10 23:55:20 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include <sys/socket.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <netdb.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <arpa/inet.h>

# include "libft.h"
# include "get_next_line.h"

typedef struct sockaddr_in SOKADR_IN;
typedef struct sockaddr SOKADR;
typedef struct in_addr I_ADR;

int		transfer_put(char *arg, int socket);
int		transfer_get(int socket);
char	*crypting(char *txt);
char	*decrypting(char *txt);

#endif
