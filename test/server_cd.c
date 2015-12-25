/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 16:01:07 by tbalea            #+#    #+#             */
/*   Updated: 2015/06/03 21:20:17 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*chdir_error(char *buff, char *src, char *cur)
{
	ft_memdel((void **)&src);
	ft_memdel((void **)&cur);
	ft_bzero(buff, ft_strlen(buff));
	return ("cd function failed.");
}

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
	if (cur[2] == '\0' || (cur[3] == '~' && cur[4] == '\0'))
		return (org);
	else if (cur[3] != '~' && cur[3] != '/')
		pat = getcwd(NULL, 0);
	else
		pat = org;
	if (cur[3] != '~')
		n++;
	res = ft_strnew(ft_strlen(cur) - 2 + ft_strlen(pat));
	i = -1;
	while (pat[++i] != '\0')
		res[i] = pat[i];
	ft_memdel((void **)&pat);
	if (cur[n] != '/')
		res[i] = '/';
	res[i + 1] = '\0';
	return (res);
}

static char *get_arg(char *buff, char *org)
{
	int		i;
	int		n;
	char	*cur;
	char	*res;

	if ((cur = ft_strtrim(buff)) == NULL)
		return (NULL);
	res = get_path(cur, org);
	n = get_barg(cur);
	i = -1;
	while (res[++i] != '\0')
		;
	i -= 1;
	while (++i && cur[++n] != '\0')
		res[i] = cur[n];
	res[i] = '\0';
	if (cur)
		ft_memdel((void **)&cur);
	cur = NULL;
	return (res);
}

char		*server_cd(char *buff, char *org)
{
	char	*src;
	char	*cur;

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
	return ("change directory succefull");
}
