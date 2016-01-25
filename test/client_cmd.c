/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 20:49:53 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/25 04:07:02 by tbalea           ###   ########.fr       */
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

static int	client_pwd(void)
{
	char	*pwd;
	int		e;

	pwd = getcwd(NULL, 0);
	ft_putendl(pwd == NULL ? "lpwd failed" : pwd);
	e = pwd ? 1 : -1;
	ft_memdel((void **)&pwd);
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
	e = chdir(des);
	ft_memdel((void **)&des);
	ft_putendl(e == 0 ? "lcd success" : "lcd failed");
	pwd = getcwd(NULL, 0);
	ft_putendl(pwd);
	ft_memdel((void **)&pwd);
	return (1);
}

static int	client_ls(char **tab)
{
	int		child;
	int		e;

	ft_bzero(tab[0], ft_strlen(tab[0]));
	ft_memcpy((void *)tab[0], (const void *)"ls\0", 3);
	if ((child = fork()) < 0)
	{
		ft_putendl("fork for lls failed");
		return (1);
	}
	if (child == 0)
	{
		execv("/bin/ls", tab);
		exit(EXIT_FAILURE);
	}
	else
		wait4(child, &e, 0, NULL);
	ft_putendl("lls succeed");
	return (1);
}

int			client_cmd(char *buf/*, int sock*/)
{
	char	**tab;
//	char	*tmp;
	int		r;
//	int		i;
//	int		fd;

	r = 0;
	tab = NULL;
//ft_putendl("spc_cmd-get-0");
//ft_putstr("buf = |");
//ft_putstr(buf);
//ft_putendl("|");
	if (buf && buf[0] != '\0')
		tab = ft_strsplit(buf, ' ');
	else
		r = 1;
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
//{
		r = client_ls(tab);
//ft_putendl("TEST");
//ft_putendl(ft_itoa(r));
//}
	else if (ft_strncmp("lpwd", buf, 4) == 0 && ft_isempty(buf[4]))
		r =client_pwd();
	else if (ft_strncmp("lcd", buf, 3) == 0 && ft_isempty(buf[3]))
		r = client_cd(tab);
/*	else if (ft_strncmp("put", buf, 3) == 0 && ft_isempty(buf[3]))// && (r = 1)
		r = send(sock, ft_strjoin("cput ", buf), 5 + ft_strlen(buf), 0);
//			&& (r = send(sock, buf, (ft_strlen(buf)), 0)) >= 0)
	{
ft_putstr("c_s_c-put:");ft_putendl(buf);
		ft_putendl((transfer_put(sock, buf)) ? "Put Ook." : "Put not Ook.");
		r = 1;
	}*/
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
/*	else if (ft_strncmp("mput", buf, 4) == 0 && ft_isempty(buf[4]))
		r = send(sock, ft_strjoin("cput ", buf), 5 + ft_strlen(buf), 0);
	else if (ft_strncmp("cput", buf, 4) == 0 && ft_isempty(buf[4]))
		buf[0] = 'n';
	{
		i = 0;
		while (tab[++i] != NULL)// && (r = send(sock, "put", 4, 0)) >= 0)
		{
			tmp = ft_strjoin("put ", tab[i]);
			ft_putstr(transfer_put(sock, tmp) ? "Put Ook " : " Put not Ook ");
			ft_putendl(tab[i]);
			ft_memdel((void **)&tmp);
		}
		r = (r >= 0) ? 1 : r;
	}*/
//	else if (ft_strncmp("mget", buf, 4) == 0 && ft_isempty(buf[4]))
//	{
//		while (tab++ && (r = send(sock, "get", ft_strlen("get"), 0)) >= 0
//				&& (r = send(sock, *tab, ft_strlen(*tab), 0)) >= 0)
//			transfer_get(sock, *tab);
//	}
//ft_putstr("PIPOPI");
	ft_tabdel(tab);
	if (r != 0 || !tab)
		ft_putstr("\n~nipaa~ ");
	return (r);
}
