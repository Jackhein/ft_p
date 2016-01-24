/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 20:49:53 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/24 21:40:23 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

/*static int	client_ls(char *buff, int sock)
{
	int		n;
	char	*rc;

	if (send(sock, ft_itoa((n = ft_strlen(buff))), 1024, 0) < 0
		|| send(sock, buff, ft_strlen(buff), 0) < 0)
		return (-1);
	ft_resizestr(&rc, -1, 1024);
	if ((n = client_rcv(sock, &rc)) == -1)
		return (-1);
	ft_resizestr(&rc, 1024, -1);
	return (1);
}*/

static int	client_pwd(char **tab)
{
	char	*pwd;
	int		e;

	pwd = getcwd(NULL, 0);
	ft_putendl(pwd);
	e = pwd ? 1 : -1;
	ft_tabdel(tab);
	ft_memdel((void **)&pwd);
ft_putstr("E = ");ft_putendl(ft_itoa(e));
	return (e);
}

static int	client_cd(char **tab)
{
	int 	e;
	char	*des;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	des = ft_strcjoin(pwd, tab[1], '/');
	ft_memdel((void **)&pwd);
	ft_memdel((void **)&des);
	e = chdir(des);
	ft_tabdel(tab);
	if (e > 0)
		ft_putendl("lcd success");
	else
		ft_putendl("lcd failed");
	pwd = getcwd(NULL, 0);
	ft_putendl(pwd);
	ft_memdel((void **)&pwd);
ft_putstr("E = ");ft_putendl(ft_itoa(e));
	return ((e < 0) ? e : 1);
}

static int	client_ls(char **tab)
{
	int		child;
	int		e;

	ft_bzero(tab[0], ft_strlen(tab[0]));
	ft_memcpy((void *)tab[0], (const void *)"ls\0", 3);
ft_putendl(tab[0]);
	if ((child = fork()) < 0)
		return (-1);
ft_putendl("popi2");
	if (child == 0)
	{
ft_putendl("popi3");
		wait4(child, &e, 0, NULL);
ft_putendl("popi4");
		ft_tabdel(tab);
ft_putendl("popi");
		return (1);
	}
	else
	{
ft_putendl("popi5");
		execv("/bin/ls", tab);
ft_putendl("popi0");
		exit(EXIT_FAILURE);
ft_putendl("popi");
	}
ft_putendl("popipo");
	return (1);
}

int			client_cmd(char *buf, int sock)
{
	char	**tab;
	int		r;
//	int		fd;

	r = 0;
//ft_putendl("spc_cmd-get-0");
//ft_putendl(buf);
	if (!buf)
		return (r);
	tab = ft_strsplit(buf, ' ');
//////////////
//	if (ft_strncmp("testo", buf, 5) == 0 && ft_isempty(buf[5]))
//	{
//		if ((fd = open(tab[1])) >= 0 && S_ISDIR(fd))
//			ft_putendl("testo-yeh");
//	}
//////////////
//	if (buf == NULL)
//		r = 0;
	if (ft_strncmp("lls", buf, 3) == 0 && ft_isempty(buf[3]))
		return (client_ls(tab));
	else if (ft_strncmp("lpwd", buf, 4) == 0 && ft_isempty(buf[4]))
		return (client_pwd(tab));
	else if (ft_strncmp("lcd", buf, 3) == 0 && ft_isempty(buf[3]))
		return (client_cd(tab));
	else if (ft_strncmp("put", buf, 3) == 0 && ft_isempty(buf[3]))// && (r = 1)
//			&& (r = send(sock, buf, (ft_strlen(buf)), 0)) >= 0)
	{
//ft_putstr("c_s_c-put:");ft_putendl(buf);
		ft_putendl((transfer_put(sock, buf)) ? "Put Ook." : "Put not Ook.");
		return (1);
	}
//	else if (ft_strncmp("get", buf, 3) == 0 && ft_isempty(buf[3]))
//{
//ft_putstr("c_s_c-get:");ft_putendl(buf);
//			if ((r = send(sock, buf, ft_strlen(buf), 0)) < 0)
//{ft_putendl("spc_cmd-get");}
//if(			 (r = send(sock, "get", ft_strlen(tab[0]), 0)) < 0)
//	return (r);ft_putendl(tab[1]);ft_putendl("testa");
//			if ((r = send(sock, tab[1], ft_strlen(tab[1]), 0)) >= 0 && (r = 1))
/*{ft_putendl("testo");*/
//		ft_putendl(transfer_get(sock, buf) ? "Get Ook." : "Get not Ook.");
//}
//ft_putendl("spc_cmd-end");}
	else if (ft_strncmp("mput", buf, 4) == 0 && ft_isempty(buf[4]) && (r = 1))
	{
		while (tab++ && (r = send(sock, "put", ft_strlen(tab[0]), 0)) >= 0)
			transfer_put(sock, *tab);
	}
//	else if (ft_strncmp("mget", buf, 4) == 0 && ft_isempty(buf[4]))
//	{
//		while (tab++ && (r = send(sock, "get", ft_strlen("get"), 0)) >= 0
//				&& (r = send(sock, *tab, ft_strlen(*tab), 0)) >= 0)
//			transfer_get(sock, *tab);
//	}
	ft_tabdel(tab);
	return (r);
}
