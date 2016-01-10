/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 16:01:07 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/07 18:17:06 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*chdir_error(char *buff, char *src, char *cur)
{
ft_putendl("brake_chdir_error_0");
	ft_memdel((void **)&src);
ft_putendl("brake_chdir_error_1");
	ft_memdel((void **)&cur);
ft_putendl("brake_chdir_error_2");
	ft_bzero(buff, ft_strlen(buff));
	return ("cd function failed.");
}
/*
static int	get_barg(char *path)
{
	if (ft_strncmp(path, "cd", 2) != 0)
		return (0);
	if (path[2] != '\0' && path[3] == '/')
		return (3);
	if (path[2] != '\0' && path[3] == '~' && path[4] == '\0')
		return (3);
	if (path[2] != '\0' && path[3] == '~' && path[4] != '\0')
		return (4);
	return (2);
}

static char	*get_path(char *cur, char *org)
{
	int		i;
	int		n;
	char	*pat;
	char	*res;

	n = 2;
ft_putendl("brake_0_0_0");
	if (cur[2] == '\0' || (cur[3] == '~' && cur[4] == '\0'))
		return (org);
	else if (cur[3] != '~' && cur[3] != '/')
		pat = getcwd(NULL, 0);
	else
		pat = org;
ft_putendl("brake_0_0_1");
	if (cur[3] != '~')
		n++;
ft_putendl("brake_0_0_2");
	res = ft_strnew(ft_strlen(cur) - 2 + ft_strlen(pat));
ft_putendl("brake_0_0_3");
	i = -1;
	while (pat[++i] != '\0')
		res[i] = pat[i];
ft_putendl(pat);
ft_putendl("brake_0_0_4");
	ft_memdel((void **)&pat);
ft_putendl("brake_0_0_5");
	if (cur[n] != '/')
		res[i] = '/';
	res[i + 1] = '\0';
ft_putendl("brake_0_0_6");
	return (res);
}
*/
static char *get_arg(char *buff, char *org)
{
	int		i;
	int		n;
//	char	*cur;
//	char	*res;

	char	*des;

	i = 2;
//ft_putendl("brake_0_0");
	while (ft_isempty(buff[i]) && buff[i] != '\0')
		i++;
//ft_putendl("brake_0_1");
	des = (char *)malloc((ft_strlen(buff) - i + 1) * sizeof(char));
	n = -1;
//ft_putendl("brake_0_2");
	while (buff[++i - 1] != '\0' && ++n >= 0)
		des[n] = buff[i - 1];
	des[n + 1] = '\0';
//ft_putendl("brake_0_3");
	free(buff);
//ft_putendl("brake_0_4");
	des = server_epur_access_arg(org, des);
//ft_putendl("brake_0_5");
	return (des);
/*	if ((cur = ft_strtrim(buff)) == NULL)
		return (NULL);
ft_putendl("brake_0_0");
	res = get_path(cur, org);
ft_putendl("brake_0_1");
	n = get_barg(cur);
ft_putendl("brake_0_2");
	i = -1;
	while (res[++i] != '\0')
		;
	i -= 1;
	while (++i && cur[++n] != '\0')
		res[i] = cur[n];
	res[i] = '\0';
ft_putendl("brake_0_3");
	if (cur)
		ft_memdel((void **)&cur);
ft_putendl("brake_0_4");
	cur = NULL;
	return (res);*/
}

char		*server_cd(char *buff, char *org)
{
	char	*src;
	char	*cur;

//ft_putendl("brake_0");
//ft_putendl("testo-0");
ft_putendl(buff);
	if ((cur = get_arg(buff, org)) == NULL)
		return (chdir_error(buff, NULL, NULL));
//ft_putendl("brake_1");
//ft_putendl("testo-1");
	src = getcwd(NULL, 0);
//	if (chdir(cur) < 0)
//		return (chdir_error(buff, src, cur));
//ft_putendl("brake_2");
//	cur = getcwd(NULL, 0);
	if (ft_strncmp(org, cur, ft_strlen(org)) != 0)
	{
//ft_putendl("brake_3");
//		if (chdir(src) < 0)
//			return (chdir_error(buff, src, cur));
//ft_putendl("brake_4");
		ft_memdel((void **)&src);
//ft_putendl("brake_5");
		ft_memdel((void **)&cur);
//ft_putendl("brake_6");
		return ("Failed to move, access denied.");
	}
	if (chdir(cur) < 0)
		return (chdir_error(buff, src, cur));
//ft_putendl("brake_7");
	ft_memdel((void **)&src);
//ft_putendl("brake_8");
	ft_memdel((void **)&cur);
//ft_putendl("brake_9");
	return ("change directory succefull");
}
