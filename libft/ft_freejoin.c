/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freejoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 13:48:57 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/25 17:45:57 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_freejoin(char const *s1, char const *s2)
{
	char	*x;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (ft_strdup((char*)s1));
	if (!s1)
		return (ft_strdup((char*)s2));
	j = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(x = (char*)malloc(sizeof(char) * j)))
		return (NULL);
	ft_strcpy(x, s1);
	ft_strcat(x, s2);
	free((char *)s1);
	return (x);
}
