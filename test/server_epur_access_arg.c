/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_epur_access_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 14:45:30 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/11 19:14:20 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*add_slash(char *arg)
{
	char	*ret;
	int		i;

	if (!arg)
		return (arg);
	i = 0;
//ft_putendl("brake_0_4_4_0");
	ret = (char *)malloc((ft_strlen(arg) + 2) * sizeof (char));
//ft_putendl("brake_0_4_4_1");
	ret[0] = '/';
	while (arg[++i - 1] != '\0')
		ret[i] = arg[i - 1];
//ft_putendl("brake_0_4_4_2");
	ret[i] = '\0';
//ft_putendl("brake_0_4_4_3");
	ft_memdel((void **)&arg);
//ft_putendl("brake_0_4_4_4");
	return (ret);
}

static int	norme(char **tab, int i)
{
//int	j;
//ft_putendl("testo-");
//for (j = 0; tab[j]; j++)
//ft_putendl(tab[j]);
//ft_putendl("testo-0");
//ft_putendl(tab[i - 1]);
//ft_putendl(tab[i]);
//ft_putendl("testo-0-0");
	ft_tabdelelem(tab, i - 1);//DELL tab[i - 1] last;
//ft_putendl("testo-0-1");
//for (j = 0; tab[j]; j++)
//ft_putendl(tab[j]);
//ft_putendl(tab[i - 1]);
//ft_putendl("testo-0-2");
	ft_tabdelelem(tab, i - 1);//DELL tab[i - 1] (..);
//for (j = 0; tab[j]; j++)
//ft_putendl(tab[j]);
//ft_putendl("testo-1");
	return (0);
}

char		*server_epur_access_arg(char *org, char *arg)
{
	char	**tab;
	int		i;

//ft_putendl("brake_0_4_0");
	if (arg == NULL)
		return (org);
//ft_putendl("arg");
//ft_putendl(arg);
	if (arg[0] == '/')
		return (arg);
	else if (arg[0] == '~')
	{
		ft_strdelelem(arg, 0);
		return (ft_strjoin(org, arg));
	}
	else
	{
//ft_putendl("brake_0_4_1");
		arg = ft_strjoin("/", arg);
		arg = ft_strjoin(getcwd(NULL, 0), arg);
//ft_putendl("<=>");
//ft_putendl("<=>");
//ft_putendl("<=>");
//ft_putendl(arg);
//ft_putendl("<=>\n#\n#\n#\n#");
		tab = ft_strsplit(arg, '/');
//ft_putendl("brake_0_4_2");
		i = 0;
		while (tab[i] != NULL)
		{
//ft_putstr(ft_itoa(i));
//ft_putstr(": ");
//ft_putstr(tab[i]);
//ft_putendl("|");
			if (ft_strcmp("..", tab[i]) == 0 && i > 0
					&& ft_strcmp("..", tab[i - 1]) != 0)
//	{tab = ft_tabdelelem(tab, i - 1);//DELL tab[i - 1] last;
//	tab = ft_tabdelelem(tab, i - 1);//DELL tab[i - 1] (..);
//	i = 0;}
				i = norme(tab, i);
			else
				i++;
//ft_putstr(ft_itoa(i));
//ft_putstr(": ");
//ft_putstr(tab[0]);
//ft_putendl("|");
		}
//ft_putendl("brake_0_4_3");
//ft_putstr(tab[0]);ft_putendl("|");
//i = 0;
		while (ft_strcmp("..", tab[0]) == 0)
			ft_tabdelelem(tab, 0);//DELL tab[0];
//ft_putendl("brake_0_4_4");
//ft_putendl("brake_0_4_5");
//ft_putendl(arg);
		arg = ft_tabjoin((const char **)tab, "/\0");
		arg = add_slash(arg);//ADD arg[0] = '/';
//ft_putendl("\n#\n#\n#\n#\n<=>");
//ft_putendl(org);
//ft_putendl(arg);
//ft_putendl("<=>");
//ft_putendl("brake_0_4_6");
		ft_tabdel(tab);//DELL tab;
//ft_putendl("brake_0_4_7");
		return (arg);
	}
}
