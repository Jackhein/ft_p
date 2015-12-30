/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 16:01:07 by tbalea            #+#    #+#             */
/*   Updated: 2015/12/29 18:03:39 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

//	To Do :
//	-Secure path ls (cf server_cd.c)
//	-Norme
/*
static int	secur_ls(char *org, char **tab)
{
	char	*src;
	char	*cur;
	int		i;

	i = 0;
	while(tab[++i] != '\0' && tab[i][0] != '-')
		;
	if (tab[i][0] != '-' && tab[i][0] != '\0')
		src = getcwd(NULL, 0);
	if ((cur = get_arg(buff, org)) == NULL)
		return (chdir_error(buff, NULL, NULL));
	src = getcwd(NULL, 0);
	if (chdir(cur) < 0)
		return (chdir_error(buff, src, cur));
	cur = getcwd(NULL, 0);
	if (ft_strncmp(org, cur, ft_strlen(org)) != 0)
	{
		if (chdir(src) < 0)
			return (chdir_error(buff, src, cur));
		ft_memdel((void **)&src);
		ft_memdel((void **)&cur);
		return ("Failed to move, access denied.");
	}
	ft_memdel((void **)&src);
	ft_memdel((void **)&cur);
}
*/
char		*server_ls(char *buff, int sock)
{
	char	**tab;
	int		i;
	int		s;
	int		child;
	int		y;

	y = -1;
	tab = ft_strsplit(buff, ' ');
	while (tab[++y])
		ft_putendl(tab[y]);
//	if (secur_ls(org, tab) < 0);
//		return ("ls function fail - Access denied");
	if ((child = fork()) < 0)
		return ("fork for ls failed");
	if (child == 0)
	{
		if (dup2(sock, 1) < 0 || dup2(sock, 2) < 0)
			exit(-1);
		execv("/bin/ls", tab);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putendl("waotong");
		wait4(child, &s, 0, NULL);
		i = -1;
		while (tab[++i])
			ft_memdel((void **)&tab[i]);
		free(tab);
		ft_putendl("waited");
		if ((WIFEXITED(s) && WEXITSTATUS(s) != 0) || WIFSIGNALED(s))
			return ("ls function fail");
		return ("ls function succeed");
	}
}
