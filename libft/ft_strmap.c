/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:21:52 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/30 19:21:54 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*sres;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	sres = (char*)malloc(ft_strlen(s) + 1);
	if (sres == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		sres[i] = f(s[i]);
		i++;
	}
	sres[i] = '\0';
	return (sres);
}
