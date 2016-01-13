/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 20:28:56 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/13 12:37:49 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <stdbool.h>
#include <errno.h>

static const char*	msg[] = {"Transfert impossible.", "Transfert possible."};

static int	perm_convert(int perm)
{
	int	oct;
	int	rem;
	int	i;

	i = 0;
	oct = 0;
	while (perm != 0)
	{
		rem = perm % 8;
		perm /= 8;
		oct += rem * i;
		i *= 10;
	}
	return (oct);
}

static int	transfer_get_check(char *name, int type)
{
	struct stat	*stats;
	int			fd;
	int			e;

ft_putstr("check-name :");ft_putendl(name);
	e = 0;
	stats = NULL;
	if ((fd = open(name, O_RDWR)) < 0 && (e = errno) != EACCES)
{ft_putstr("check-error :");ft_putendl("0");
	type = 1;
}	else if (e == EACCES)
{ft_putstr("check-EACCES :");ft_putendl(ft_itoa(e));
		return (0);
}	else if ((e = fstat(fd, stats)) < 0)
	{
ft_putstr("check-FD :");ft_putendl(ft_itoa(e));
		close(fd);
		return (0);
	}
	else if (S_ISDIR(stats->st_mode))
	{
ft_putstr("check-S_ISDIR :");ft_putendl("1");
		close(fd);
		free(stats);
		return (type ? 3 : 0);
	}
ft_putstr("check-OK :");ft_putendl("Ook");
	close(fd);
	free(stats);
	return (type ? 2 : 1);
}

static int	transfer_get_dir(int socket, char **tab, bool exist)
{
	int		e;
	char	buf[1024];

//	if ((e = recv(socket, buf, 1024, 0)) < 0
	if ((!exist && (e = mkdir(tab[1], perm_convert(ft_atoi(tab[3])))) < 0)
			|| (e = chdir(tab[1])) < 0)
	{
		ft_tabdel(tab);
//		ft_memdel((void **)&buf);
		return (e);
	}
//	ft_memdel((void **)&name);
	while (e >= 0 && (e = recv(socket, buf, 1024, 0)) >= 0
			&& ft_strcmp(buf, "end put") != 0)
//			&& (e = recv(socket, buf, 1024, 0)) >= 0)
		e = transfer_get(socket, buf);
	ft_tabdel(tab);
	ft_memdel((void **)&buf);
	return ((e < 0 || (e = chdir("..")) < 0) ? e : 1);
}

static int	transfer_get_file(int socket, char **tab)
{
	int		e;
	int		fd;
	off_t	eof;
	char	buf[1024];
	char	*crypt;

//ft_putendl(name);
//	if ((fd = recv(socket, buf, 1024, 0)) < 0
			if ((fd = open(tab[1], O_CREAT, perm_convert(ft_atoi(tab[3])))) < 0)
	{
		ft_tabdel(tab);
//		ft_memdel((void **)&name);
//		ft_memdel((void **)&buf);
		return (fd);
	}
//ft_putstr("Perm : ");
//ft_putendl(buf);
	ft_tabdel(tab);
//	ft_memdel((void **)&name);
	while (((e = recv(socket, buf, 1024, 0)) >= 0
			&& ft_strcmp(buf, "end put") != 0) || e < 0)
	{
		crypt = decrypting(buf);
		eof = lseek(fd, 0, SEEK_END);
		e = write(eof, crypt, ft_strlen(buf));
		ft_memdel((void **)&crypt);
	}
	close(fd);
	ft_tabdel(tab);
	ft_memdel((void **)&buf);
	return (e < 0 ? e : 1);
}

int			transfer_get(int socket, char *arg)
{
	char	**tab;
//	char	*name;
	char	buf[1024];
	int		e;
	int		type;
ft_putendl("get-0");
ft_putendl(arg);
	tab = ft_strsplit(arg, ' ');
//	if ((e = recv(socket, buf, 1024, 0)) < 0)
//		return (e);
//	name = ft_strdup(buf);
	ft_putendl(msg[(type = transfer_get_check(tab[1], ft_atoi(tab[1])))? 1 : 0]);
	if ((e = send(socket, msg[type ? 1 : 0], ft_strlen(msg[type? 1 : 0]), 0)) < 0
			|| type == 0)
	{
		ft_tabdel(tab);
//		ft_memdel((void **)&buf);
		return ((e < 0) ? e : 1);
	}
	else if (type == 3)
		e = transfer_get_dir(socket, tab, false);
//		function get_dir with FLAG already existing
	else if (type == 2)// && ft_strcmp("directory", buf) == 0)
//		function get_dir without FLAG already existing
		e = transfer_get_dir(socket, tab, true);
	else if (type == 1)// && ft_strcmp(buf, "file") == 0)
//		function get_file
		e = transfer_get_file(socket, tab);
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
