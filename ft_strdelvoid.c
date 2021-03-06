/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelvoid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 17:19:58 by tbalea            #+#    #+#             */
/*   Updated: 2015/12/30 20:38:56 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	jump_space(const char *str, int j)
{
	int	n;

	n = 0;
	if (str && str[j] != '\0'
			&& str[j] != ' ' && str[j] != '\t' && str[j] != '\n')
		return (1);
	while (str && str[j + n] != '\0'
			&& (str[j + n] == ' ' || str[j + n] == '\t' || str[j + n] == '\n'))
		n++;
	return (n);
}

static int	new_size(const char *str)
{
	int	i;
	int	n;
	int	s;

	s = 1;
	n = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str && str[i] != '\0'
			&& (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	while (str && str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			s = 1;
		else
		{
			n += 1 + s;
			s = 0;
		}
		i++;
	}
	return (n);
}

char		*ft_strdelvoid(char *str)
{
	char	*new;
	int		t;
	int		i;
	int		j;

	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	t = new_size(str);
	if ((new = (char *)malloc(t * sizeof(char *))) == NULL)
		return (NULL);
	while (str && str[j] != '\0'
			&& (str[j] == ' ' || str[j] == '\t' || str[j] == '\n'))
		j++;
	while (++i < (t - 1))
	{
		new[i] = str[j];
		j += jump_space(str, j);
	}
	new[i] = '\0';
	ft_bzero(str, ft_strlen(str));
	free(str);
	return (new);
}
