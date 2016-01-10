/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 10:23:51 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/08 10:48:25 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static const char* msg[] = {"fork for lls failed",
	"lls function fail", "lls function succeed"};

static void	client_ls_error(char **tab, int i)
{
	ft_putendl(msg[i]);
	ft_tabdel(tab);
}

void		client_ls(char *buff)
{
	char	**tab;
	int		s;
	int		child;

	buff = ft_strdelelem(buff, 0);
	tab = ft_strsplit(buff, ' ');
//	if (pipe(pipefd) < 0)// || pipe(pipefdrecv) < 0)
//		return (client_ls_error(tab, 0));
	if ((child = fork()) < 0)
		return (client_ls_error(tab, 0));
	else if (child == 0)
	{
//		if (dup2(pipefd[0], 0) < 0)
//			exit(-1);
		wait4(child, &s, 0, NULL);
		if ((WIFEXITED(s) && WEXITSTATUS(s) != 0) || WIFSIGNALED(s))
			return (client_ls_error(tab, 1));
//		while ((n = read(pipefd[0], buf, 1024)) >= 1024)
//			ft_putstr(buf)
//		ft_putendl(buf);
	}
	else
	{
//		if (dup2(pipefd[1], 1) < 0 || dup2(pipefd[1], 2) < 0)
//			exit(-1);
		execv("/bin/ls", tab);
		exit(EXIT_FAILURE);
	}
	return (client_ls_error(tab, 2));
}
				
