/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 16:01:07 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/24 20:45:12 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <errno.h>
//	To Do :
//	-Secure path ls (cf server_cd.c)
//	-Norme
//	-Read the output (dup to the child);

static int	secur_ls(char *org, char *buff)
{
	char	**tab;
	char	*arg;
	int		i;
	int		j;

	i = 1;
	j = 0;
	tab = ft_strsplit(buff, ' ');
	while (tab[i] && tab[i][0] == '-')
		i++;
	while (i-- > 0)
		ft_tabdelelem(tab, 0);
	if (tab[0] == NULL)
		return (0);
	arg = ft_tabjoin((const char **)tab, "\0");
	ft_tabdel(tab);
	i = 0;
	i = ft_strncmp(org, server_epur_access_arg(org, arg), ft_strlen(org));
	ft_memdel((void **)&arg);
	return (i);
}

char		*server_ls(char *buff, char *org, int sock)
{
	char	**tab;
	int		i;
	int		s;
	int		child;

	int		pipefd[2];
//	int		*pipefd;
	char	buf[1024];
	int		n;

//pipefd = (int *)malloc(2 * sizeof(int));
//ft_putstr("ORG = ");ft_putendl(org);
//ft_putstr("buff = ");ft_putendl(buff);
	if (secur_ls(org, buff) != 0)
		return ("ls function fail - Access denied");
	tab = ft_strsplit(buff, ' ');
	if (pipe(pipefd) < 0)// || pipe(pipefdrecv) < 0)
		return ("pipe for ls failed");
	else if ((child = fork()) < 0)
		return ("fork for ls failed");
	else if (child == 0)
	{
//		if (close(pipefd[1]) < 0)// || close(pipefdsend[0]) < 0)
//			return ("ls function fil - close error");
/*		if ((WIFEXITED(s) && WEXITSTATUS(s) != 0) || WIFSIGNALED(s))
{ft_putendl("ERROR:");
ft_putendl(strerror(errno));
			return ("ls function fail");
}*/
		if (dup2(pipefd[0], 0) < 0)
			exit(-1);
		wait4(child, &s, 0, NULL);
		i = -1;
		while (tab[++i])
			ft_memdel((void **)&tab[i]);
		free(tab);
//ft_putendl("LS 0");
//ft_putendl("LS 1");
		while ((n = read(pipefd[0], buf, 1024)) >= 1024)
		{
//			if (send(sock, ft_itoa(n), 1024, 0) < 0)
//				return ("ls function fail");
//ft_putendl("LS 2");
			if ((send(sock, buf, n, 0) < 0))
				return ("ls function fail");
		}
//ft_putendl("LS 3");
		if (//send(sock, ft_itoa(n), 1024, 0) < 0
				(send(sock, buf, n, 0) < 0))
			return ("ls function fail");
	}
	else
	{
//		if (close(pipefd[0]) < 0)// || close(pipefdsend[0]) < 0)
//			return ("ls function fil - close error");
//ft_putendl("0 LS");
		if (dup2(pipefd[1], 1) < 0 || dup2(pipefd[1], 2) < 0)
//{ft_putendl("ERROR:");
//ft_putendl(strerror(errno));
			exit(-1);
//}
//ft_putendl("1 LS");
		execv("/bin/ls", tab);
//ft_putendl("2 LS");
		exit(EXIT_FAILURE);
	}
	return ("ls function succeed");
}
/*
static int	server_ls_child_send(int *pipefd, int child, int sock, char **tab)
{
	int		s;
	int		i;
	int		n;
	char	buf[1024];

//	if (close(pipefd[1]) < 0)// || close(pipefdsend[0]) < 0)
//		return ("ls function fil - close error");
	if (dup2(pipefd[0], 0) < 0)
		exit(-1);
	wait4(child, &s, 0, NULL);
	i = -1;
	ft_tabdel(tab);
	if ((WIFEXITED(s) && WEXITSTATUS(s) != 0) || WIFSIGNALED(s))
		return (-1);
	while ((n = read(pipefd[0], buf, 1024)) >= 1024)
	{
//		if (send(sock, ft_itoa(n), 1024, 0) < 0)
//			return ("ls function fail");
		if ((send(sock, buf, n, 0) < 0))
			return (-1);
	}
	if (*//*send(sock, ft_itoa(n), 1024, 0) < 0*//* (send(sock, buf, n, 0) < 0))
		return (-1);
	return (1);
}

static void	server_ls_child_exec(int *pipefd, char **tab)
{
//	if (close(pipefd[0]) < 0)// || close(pipefdsend[0]) < 0)
//		return ("ls function fil - close error");
	if (dup2(pipefd[1], 1) < 0 || dup2(pipefd[1], 2) < 0)
		exit(-1);
	execv("/bin/ls", tab);
	exit(EXIT_FAILURE);
}

char		*server_ls(char *buff, char *org, int sock)
{
	char	**tab;
//	int		s;
	int		child;
	int		pipefd[2];

	if (secur_ls(org, buff) != 0)
		return ("ls function fail - Access denied");
	tab = ft_strsplit(buff, ' ');
	if (pipe(pipefd) < 0)// || pipe(pipefdrecv) < 0)
		return ("pipe for ls failed");
	else if ((child = fork()) < 0)
		return ("fork for ls failed");
	else if (child == 0 && server_ls_child_send(pipefd, child, sock, tab) < 0)
		return ("ls function fail");
	else
		server_ls_child_exec(pipefd, tab);
	return ("ls function succeed");
}*/
