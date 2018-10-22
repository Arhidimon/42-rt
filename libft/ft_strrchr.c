/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 13:45:57 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/29 13:45:59 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*pos;
	size_t	i;

	i = 0;
	pos = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			pos = (char*)(s + i);
		i++;
	}
	if (s[i] == (char)c)
		pos = (char*)(s + i);
	return (pos);
}
