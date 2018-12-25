/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:31:47 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/31 18:31:51 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l || len > l || len + start > l)
		return (NULL);
	ptr = (char*)malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[len] = '\0';
	while (len--)
		ptr[len] = s[start + len];
	return (ptr);
}
