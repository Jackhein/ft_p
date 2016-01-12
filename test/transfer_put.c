/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 16:24:26 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/11 20:02:58 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
**
**	Encrypt send file
**
*/

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

static int	transfer_put_permission(int socket, int fd, DIR *dir)
{
	struct stat		*stats;
	int				othr;
	int				team;
	int				user;

	stats = NULL;
	if (fstat(fd, stats) < 0)
		return (transfer_put_error(socket, 0, fd, dir));
	user = (stats->st_mode & S_IRUSR) ? 1 : 0;
	user += (stats->st_mode & S_IWUSR) ? 2 : 0;
	user += (stats->st_mode & S_IXUSR) ? 4 : 0;
	team = (stats->st_mode & S_IRGRP) ? 1 : 0;
	team += (stats->st_mode & S_IWGRP) ? 2 : 0;
	team += (stats->st_mode & S_IXGRP) ? 4 : 0;
	othr = (stats->st_mode & S_IROTH) ? 1 : 0;
	othr += (stats->st_mode & S_IWOTH) ? 2 : 0;
	othr += (stats->st_mode & S_IXOTH) ? 4 : 0;
	free(stats);
	if (user != 3 || user != 7)
		return (transfer_put_error(socket, 1, fd, dir));
	if (send(socket, ft_strjoin(ft_itoa(user), ft_strjoin(ft_itoa(team),\
						ft_itoa(othr))), ft_strlen(ft_strjoin(ft_itoa(user),\
					ft_strjoin(ft_itoa(team), ft_itoa(othr)))) , 0) < 0)
		return (-2);
	return (1);
}

static int	transfer_put_file(char *buf, int socket, int fd)
{
	int		e;
	char	*crypt;

ft_putendl("put-file-0");
	if (ft_strcmp("is a directory", buf) == 0)
		return (transfer_put_error(socket, 2, fd, NULL));
ft_putendl("put-file-1");
	if ((e = send(socket, "file", 5, 0)) < 0)
		return (e);
ft_putendl("put-file-2");
	if ((e = transfer_put_permission(socket, fd, NULL)) <= 0)
		return (transfer_put_error(socket, 1, fd, NULL));
ft_putendl("put-file-3");
	while ((e = read(fd, buf, 1024)) >= 0 && e >= 0)
	{
ft_putendl("put-file-4");
		crypt = crypting(buf);
		e = send(socket, crypt, ft_strlen(crypt), 0);
		ft_memdel((void **)&crypt);
ft_putendl("put-file-5");
	}
	close(fd);
	crypt = crypting(buf);
ft_putendl("put-file-6");
	if (e >= 0)
		e = send(socket, crypt, ft_strlen(crypt), 0) < 0;
ft_putendl("put-file-7");
	ft_memdel((void **)&crypt);
	ft_memdel((void **)&buf);
	return ((e < 0 || (e = send(socket, "end put", 8, 0)) < 0) ? e : 1);
}

static int	transfer_put_dir(int socket, DIR *dir, char *arg)
{
	int				e;
	struct dirent	*content;

ft_putendl("put-dir-0");
	content = NULL;
	if ((e = send(socket, "directory", 10, 0)) < 0)
		return (e);
ft_putendl("put-dir-1");
	if ((e = transfer_put_permission(socket, dirfd(dir), dir)) <= 0)
		return (transfer_put_error(socket, 1, -1, dir));
ft_putendl("put-dir-2");
	while ((content = readdir(dir)) && e >= 0)
		e = transfer_put(ft_strjoin(arg, content->d_name), socket);
ft_putendl("put-dir-3");
	closedir(dir);
	free(content);
	if (e < 0)
		return (e);
	return (1);
}

int			transfer_put(char *arg, int socket)
{
	char			buf[1024];
	DIR				*dir;
	int				fd;
	int				e;

ft_putendl("put-0");
	if ((e = send(socket, "put", 4, 0)) < 0
			|| (e = send(socket, arg, ft_strlen(arg), 0)) < 0
			|| (e = recv(socket, buf, 1024, 0)) < 0)
		return (e);
ft_putendl("put-1");
	if (ft_strcmp("is a file", buf) == 0 || ft_strcmp("no right", buf) == 0)
		return (transfer_put_error(socket, 0, -1, NULL));
	else if ((fd = open(arg, 0)) >= 0 && !S_ISDIR(fd))
	{
ft_putendl("put-2");
		if ((e = transfer_put_file(buf, socket, fd)) < 0)
			return (e);
	}
	else if ((dir = opendir(arg)))
	{
ft_putendl("put-3");
		if ((e = transfer_put_dir(socket, dir, arg)) < 0)
			return (e);
	}
	if ((e = send(socket, "end put", 8, 0)) < 0)
		return (e);
ft_putendl("put-4");
	ft_memdel((void **)&buf);
	return (1);
}
