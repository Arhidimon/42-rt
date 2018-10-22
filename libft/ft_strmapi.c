/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:22:47 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/30 19:22:50 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*sres;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	sres = (char*)malloc(ft_strlen(s) + 1);
	if (sres == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		sres[i] = f(i, s[i]);
		i++;
	}
	sres[i] = '\0';
	return (sres);
}
