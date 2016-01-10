/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 20:28:56 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/10 16:37:14 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/**
 *	NORME
 *	PERMISSION
 *	BINARY
 *	END OF PUT
**/
static const char*	msg[] = {"name disponible", "is a directory", "is a file",
	"no right"};

static int	transfer_get_error(int socket, int error);

static int	transfer_get_check(int socket, char *name)
{
	struct stat	*stats;
	int			fd;
	int			e;

	stats = NULL;
	if ((fd = open(name, O_RDWR)) < 0 && fd != EACCES)
		return (0);
	else if (fd == EACCES)
		return (3);
	else if ((e = fstat(fd, stats)) < 0)
	{
		close(fd);
		return (e);
	}
	else if (S_ISDIR(stats->st_mod))
	{
		close(fd);
		free(stats);
		return (1);
	}
	close(fd);
	free(stats);
	return (2);
}

static int	transfer_get_dir(int socket, char *name, bool exist)
{
	int		e;
	char	buf[1024];

	if ((e = recv(socket, buf, 1024, 0)) < 0
			|| (!exist && (e = mkdir(name, /*FLAG RIGHT*/)) < 0)
			|| (e = chdir(name)) < 0)
	{
		ft_memdel((void **)&name);
		ft_memdel((void **)&buf);
		return (e);
	}
	ft_memdel((void **)&name);
	while (e >= 0 && (e = recv(socket, buf, 1024, 0)) >= 0
			&& ft_strcmp(buf, "end put") != 0
			&& (e = recv(socket, buf, 1024, 0)) >= 0)
		e = transfer_get(socket);
	ft_memdel((void **)&buf);
	if (e < 0 || (e = chdir("..")) < 0)
		return (e);
	return (1);
}

static int	transfer_get_file(int socket, char *name)
{
	int		e;
	int		fd;
	off_t	eof;
	char	buf[1024];

	if ((fd = recv(socket, buf, 1024, 0)) < 0
			|| (fd = open(name, O_CREAT, /*FLAG RIGHT*/)) < 0)
	{
		ft_memdel((void **)&name);
		ft_memdel((void **)&buf);
		return (fd);
	}
	ft_memdel((void **)&name);
	while (((e = recv(socket, buf, 1024, 0)) >= 0
			&& ft_strcmp(buf, "end put") != 0) || e < 0)
	{
		eof = lseek(fd, 0, SEEK_END);
		e = write(eof, transfer_decrypt(buf), ft_strlen(buf));
	}
	close(fd);
	ft_memdel((void **)&buf);
	if (e < 0)
		return (e);
	return (1);
}

int			transfer_get(int socket)
{
	char		*name;
	char		buf[1024];
	int			e;
	int			type;

	if ((e = recv(socket, buf, 1024, 0)) < 0)
		return (e);
	name = ft_strdup(buf);
	ft_putendl(msg[(type = transfer_get_check(socket, name))]);
	if ((e = send(socket, msg[type], ft_strlen(msg[e]), 0)) < 0
			|| type > 1 || (e = recv(socket, buf, 1024, 0)) < 0
			|| ft_strcmp(buf, "end put") == 0)
	{
		ft_memdel((void **)&buf);
		return ((e < 0) ? e : 1);
	}
	else if (type == 1 && ft_strcmp("directory", buf) == 0)
		e = transfer_get_dir(socket, name, false);
//		function get_dir with FLAG already existing
	else if (type == 0)
	{
//		function get_dir without FLAG already existing
		if (ft_strcmp("directory", buf) == 0)
			e = transfer_get_dir(socket, name, true);
//		function get_file
		else if (ft_strcmp(buf, "file") == 0)
			e = transfer_get_file(socket, name);
	}
	ft_memdel((void **)&buf);
	return (e);
}

//	1
/*	{
		if ((e = chdir(name)) < 0 || (e = recv(socket, buf, 1024, 0)) < 0)
			return (e);
		while (e >= 0 && (e = recv(socket, buf, 1024, 0)) >= 0
				&& ft_strcmp(buf, "end put") != 0)
		{
			if ((e = recv(socket, buf, 1024, 0)) < 0)
				return (e);
			e = transfer_get(socket, );
		}
		if ((e = chdir("..")) < 0)
			return (e);
	}*/

//	2
/*		{
			if ((e = recv(socket, buf, 1024, 0)) < 0
				|| (e = mkdir(name, *//*FLAG RIGHT*//*)) < 0
				|| (e = chdir(name)) < 0)
				return (e);
			while (e >= 0 && (e = recv(socket, buf, 1024, 0)) >= 0
					&& ft_strcmp(buf, "end put") != 0)
			{
				if ((e = recv(socket, buf, 1024, 0)) < 0)
					return (e);
				e = transfer_get(socket, );
			}
			if ((e = chdir("..")) < 0)
				return (e);
		}*/

//3
/*		{
			if ((fd = recv(socket, buf, 1024, 0)) < 0
					|| (fd = open(name, O_CREAT, *//*FLAG RIGHT*//*)) < 0)
				return (fd);
			while ((e = recv(socket, buf, 1024, 0)) >= 0
					&& ft_strcmp(buf, "end put") != 0)
			{
				eof = lseek(fd, 0, SEEK_END);
				write(eof, transfer_decrypt(buf), ft_strlen(buf));
			}
			eof = lseek(fd, 0, SEEK_END);
			write(eof, buf, ft_strlen(buf));
		}*/
