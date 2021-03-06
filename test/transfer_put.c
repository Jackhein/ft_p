/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 16:24:26 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/25 04:11:48 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

//#include <errno.h>
//#include <stdio.h>

/*
**
**	ERROR in
**	PERM => OCTAL ('0'---)
**	FT_MEMDEL to readd
**
*/
/*
static const char* msg[] = {"fstats function error", "no permission",
	"Name already taken"};

static int	transfer_put_error(int socket, int error, int fd, DIR *dir)
{
	if (dir)
		closedir(dir);
	if (fd >= 0)
		close(fd);
	ft_putendl(msg[error]);
	if (send(socket, "end put", 8, 0) < 0
			|| send(socket, msg[error], ft_strlen(msg[error]), 0) < 0)
		return (-2);
	return (-1);
}
*/
static char	*transfer_put_stat(int fd, int type, char *name)
{
	struct stat		*stats;
	int				perm;

//int	e;
//ft_putstr("FD=");
//ft_putendl(ft_itoa(fd));
	stats = (struct stat *)malloc(sizeof(struct stat));
	if ((fstat(fd, stats)) < 0)
//{e = errno;ft_putstr("ERROR=");ft_putendl(strerror(e));
		return (NULL);
//}
//printf("PUT_STAT_TYPE:%i\n", type);
//ft_putendl("Stat-fstat :Ook.");
//		return (transfer_put_error(socket, 0, fd, dir));
	perm = (stats->st_mode & S_IRUSR) ? 100 : 0;
	perm += (stats->st_mode & S_IWUSR) ? 200 : 0;
	perm += (stats->st_mode & S_IXUSR) ? 400 : 0;
	perm += (stats->st_mode & S_IRGRP) ? 10 : 0;
	perm += (stats->st_mode & S_IWGRP) ? 20 : 0;
	perm += (stats->st_mode & S_IXGRP) ? 40 : 0;
	perm += (stats->st_mode & S_IROTH) ? 1 : 0;
	perm += (stats->st_mode & S_IWOTH) ? 2 : 0;
	perm += (stats->st_mode & S_IXOTH) ? 4 : 0;
//ft_putstr("Stat-stats :");ft_putendl(ft_strjoin(ft_itoa(user), ft_strjoin(ft_itoa(team), ft_itoa(othr))));
	free(stats);
//ft_putstr("User = ");ft_putendl(ft_itoa(user));
	if (perm / 100 != 3 && perm / 100 != 7)
		return (NULL);
//ft_putstr("Stat-Ook ?");ft_putendl("Ook.");
//ft_putstr("PUT_STAT_RET=");
	ft_putendl(ft_strcjoin(name, ft_strcjoin(ft_itoa(type),\
			ft_itoa(perm), ' '), ' '));
	return (ft_strcjoin(name, ft_strcjoin(type ? "1" : "0", ft_itoa(perm), ' '),\
			' '));
//		return (transfer_put_error(socket, 1, fd, dir));
//	if (send(socket, ft_strjoin(ft_itoa(user), ft_strjoin(ft_itoa(team),\
//						ft_itoa(othr))), ft_strlen(ft_strjoin(ft_itoa(user),\
//					ft_strjoin(ft_itoa(team), ft_itoa(othr)))) , 0) < 0)
//		return (-2);
//	return (1);
}

static int	transfer_put_file(/*char *buf, */int socket, int fd)
{
	int		e;
char	*buf;

buf = NULL;
buf = (char *)malloc(1024 * sizeof(char));
//	char	*crypt;

//ft_putendl("put-file-0");
//ft_putstr("What is iit ? ");
//ft_putendl(buf);
//	if (ft_strcmp("is a directory", buf) == 0)
//		return (transfer_put_error(socket, 2, fd, NULL));
//	if ((e = send(socket, "file", 5, 0)) < 0)
//		return (e);
//	if ((e = transfer_put_stat(socket, fd, NULL)) <= 0)
//		return (transfer_put_error(socket, 1, fd, NULL));
//	ft_memdel((void **)&buf);
//ft_putendl("PUT_FILE");
	e = 0;
	while (e >= 0 && (e = read(fd, buf, 1024)) > 0)
	{
//		crypt = crypting(buf);
//		e = send(socket, crypt, ft_strlen(crypt), 0);i
		e = send(socket, buf, ft_strlen(buf), 0);
//ft_putendl(buf);
//ft_putendl("||||||||||||||||||||||||||||||||||||");
		ft_bzero(buf, 1024);
//		ft_memdel((void **)&crypt);
	}
	close(fd);
//	crypt = crypting(buf);
//	if (e >= 0)
//		e = send(socket, crypt, ft_strlen(crypt), 0);
//		e = send(socket, buf, ft_strlen(buf), 0);
	sleep(1);
//	ft_memdel((void **)&crypt);
//	ft_memdel((void **)&buf);
	return ((e < 0 || (e = send(socket, "end put", 8, 0)) < 0) ? e : 1);
}

static int	transfer_put_dir(int socket, DIR *dir, int fd, char *des)
{
	int				e;
//	char			*name;
//	char			**tab;
	struct dirent	*content;

	content = NULL;
//	tab = ft_strsplit(data, ' ');
//	if ((e = send(socket, "directory", 10, 0)) < 0)
//		return (e);
//	if ((e = transfer_put_permission(socket, dirfd(dir), dir)) <= 0)
//		return (transfer_put_error(socket, 1, -1, dir));
//	name = ft_strdup(tab[1]);
	while ((content = readdir(dir)) && e >= 0)
	{
		if (ft_strcmp(content->d_name, ".") == 0
				|| ft_strcmp(content->d_name, "..") == 0)
			continue ;
//		ft_memdel((void **)&tab[1]);
//ft_putstr("READDIR:");
//ft_putendl(content->d_name);
//ft_putstr("CHDIR:");
//ft_putendl(des);
		if ((e = chdir(des)) < 0)
			break ;
//		tab[1] = ft_strdup(content->d_name);
		e = transfer_put(socket, ft_strjoin("put ", content->d_name));
		if ((e = chdir("..")) < 0)
			break ;
//		e = transfer_put(socket, ft_tabjoin((const char **)tab, " "));
	}
//	ft_tabdel(tab);
	close(fd);
	closedir(dir);
	free(content);
//	if (e < 0)
//		return (e);
//	if ((e = send(socket, "end put", 8, 0)) < 0)
//		return (e);
//	return (1);
	return ((e < 0) ? e : ((e = send(socket, "end dir", 8, 0)) < 0) ? e : 1);
}

int			transfer_put(int socket, char *arg)
{
	char	buf[1024];
	char	*data;
	DIR		*dir;
	int		fd;

	char	**tab;
	int		e;

	tab = ft_strsplit(arg, ' ');
//ft_putendl(tab[1]);
	e = 0;
//ft_putendl("put-0");
//	if ((e = send(socket, "end put", 8, 0)) < 0)
//		return (e);
//ft_putendl("put-1");
//ft_putendl(arg);
//e = 0;
//ft_putendl("PLUTOT");
	if ((dir = opendir(tab[1])) > 0 && (fd = dirfd(dir)) > 0
			&& (data = transfer_put_stat(fd, 1, ft_strcjoin(tab[0], tab[1], ' ')))
			&& send(socket, data, ft_strlen(data), 0) > 0)
	{
//ft_putendl("put-1-1");
//ft_putendl(data);
		e = recv(socket, buf, 1024, 0);
		ft_putendl(buf);
   		if (e < 0 || ft_strcmp("Transfert impossible.", buf) == 0
//				|| (e = transfer_put_dir(socket, dir, fd, data)) < 0)
				|| (e = transfer_put_dir(socket, dir, fd, tab[1])) < 0)
			return ((e < 0) ? -1 : 0);
		return (1);
//		if (ft_strcmp("Transfert impossible", buf) == 0)
//			return (0);
//		if ((e = transfer_put_dir(socket, dir, fd, data)) < 0)
//			return (e);
	}
	else if ((fd = open(tab[1], 0)) > 0
			&& (data = transfer_put_stat(fd, 0, ft_strcjoin(tab[0], tab[1], ' ')))
			&& (e = send(socket, data, ft_strlen(data), 0)) > 0)
//		if ((e = transfer_put_permission(socket, fd, NULL)) <= 0)
//	if ((e = send(socket, "put", 4, 0)) < 0
//			|| (e = send(socket, arg, ft_strlen(arg), 0)) < 0
//			|| (e = recv(socket, buf, 1024, 0)) < 0)
//		return (e);
	{
//ft_putendl("put-1-0");
//ft_putendl(data);
//ft_putendl(arg);
//ft_putendl("PUT");
		e = recv(socket, buf, 1024, 0);
		ft_putendl(buf);
		if (e < 0 || ft_strcmp("Transfert impossible.", buf) == 0
				|| (e = transfer_put_file(/*buf, */socket, fd)) < 0)
			return ((e < 0) ? -1 : 0);
		return (1);
//		if (ft_strcmp("Transfert impossible", buf) == 0)
//			return (0);
//		if ((e = transfer_put_file(buf, socket, fd)) < 0)
//			return (e);
	}
//	if (ft_strcmp("is a file", buf) == 0 || ft_strcmp("no right", buf) == 0)
//		return (transfer_put_error(socket, 0, -1, NULL));
//	else if ((fd = open(arg, 0)) >= 0 && !S_ISDIR(fd))
//	{
//		if ((e = transfer_put_file(buf, socket, fd)) < 0)
//			return (e);
//	}
	ft_tabdel(tab);
//ft_putstr("Nombres de conditions :");ft_putendl(ft_itoa(e));
//ft_putendl("put-2");
//	ft_memdel((void **)&arg);
//	ft_memdel((void **)&buf);
//	ft_memdel((void **)&data);
	return (0);
}
