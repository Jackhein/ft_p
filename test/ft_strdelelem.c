/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 10:48:43 by tbalea            #+#    #+#             */
/*   Updated: 2016/01/08 10:51:24 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#inlcude "libft.h"

void	ft_strdelelem(char **str, int i)
{
	if (!str || i < 0 || i > ft_strlen(str))
		return ;
	while (str[++i])
		str[i - 1] = str[i];
	str[i - 1] = '\0';
}