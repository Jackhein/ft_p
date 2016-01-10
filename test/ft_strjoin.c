/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-heyge <nd-heyge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 20:22:30 by nd-heyge          #+#    #+#             */
/*   Updated: 2016/01/07 00:06:07 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

//ft_putendl("\n<=A=>");
//ft_putendl(s1);
//ft_putendl("\n");
//ft_putendl(s2);
//ft_putendl("\n");
	if (s1 == NULL && s2)
		str = ft_strdup(s2);
	else if (s2 == NULL && s1)
		str = ft_strdup(s1);
	else if (s2 == NULL && s1 == NULL)
		return (NULL);
	else
	{
		str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (str)
			str = ft_strcat(ft_strcat(str, s1), s2);
	}
//ft_putendl(str);
//ft_putendl("<=V=>\n");
	return (str);
}
