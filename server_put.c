/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 05:58:10 by tbalea            #+#    #+#             */
/*   Updated: 2015/12/23 18:38:09 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

//1 for get
//2 for put
static int	transfert_fil()
{
	send(s, ft_itoa(n), ft_strlen(ft_itoa(n)) + 1, 0);
	send(s, file_name, ft_strlen(file_name) + 1, 0);
	read();
	send(s, buff, ft_strlen(buff) + 1, 0);
}

static int	transfert_dir(char *file, int p, int s)
{
	int	i;

	i = -1;
	send(ft_itoa(--p));
	if (opendir(file))
	{
		if ((d = readd(file)))
		{
			while(d.d_name[++i])
				server_transfert(org, p);
		}
		else
			ft_putendl("read error");
	}
	else
	{
		ft_putendel("open error");
	}
	close(fd);
	send(ft_itoa(p))
}

static char	*cd_file(char *pwd, char *file, char *org, int s)
{
	char	*path;
	char	*fres;
	int		n;
	int		m;
	int		i;

	n = ft_strlen(pwd) + 1;
	m = ft_strlen(file);
	while (--m >= 0 && file[m] != '/')
		;
	n += m;
	fres = ft_strnew(ft_strlen(file) - m);cc
	path = ft_strnew(n);
	n = -1;
	while (pwd[++n] != '\0')
		path[n] = pwd[n];
	i = -1;
	while (++i < m)
		path[n + i] = file[i];
	path[n + i] = '\0';
	i = -1;
	while (file[++m] != '\0' && ++i >= 0)
		fres[i] = file[m];
	if (ft_strncmp(server_cd(path, org), org, ft_strlen(org)) == 0)
	{
		ft_memdel((void)&path);
		return (fres);
	}
	ft_memdel((void)&path);
	return (NULL);
}

static void	transfert_arg(char *org, char *pwd, char *arg, int p)
{
	char	*file;
	int		fd;

	if (!(file = cd_file(getcwd(NULL, 0), arg)))
		return (0);
	if ((fd = open(getcwd(NULL, 0), file)) < 0)
		;
	if (ftstat(fd, stat) == 0)
		;
	if (S_IFDIR(s.st_mode))
		transfert_dir(file);
	else if (S_IFREG(s.st_mode))
		transfert_fil();
	else
		;
	server_cd(pwd);
	return ()
}

char		*server_transfert(char *buff, char *org, int s)
{
	char	**tab;
	char	*pwd;
	int		i;
	int		n;

	n = 1;
	i = 0;
	if (!(tab = ft_strsplit(buff, ' ')))
		return ("Tranfert error : split argument error.")
	if (!tab[0] || !tab[1])
	{
		ft_tabdel((void)&tab);
		return ("Usage : \"put file1 file2\".");
	}
	pwd = getcwd(NULL, 0);
	while (tab[++i] && n)
		n = transfert_arg(tab[i], pwd, org, 0);
	ft_tabdel((void)&tab);
	ft_memdel((void)&pwd);
	if (n == 0)
		return ("Failed to find file(s)");
	return ("Transfert succeeded");
}
