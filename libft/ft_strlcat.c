/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 12:55:54 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/29 12:55:56 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*dst)
	{
		j++;
		dst++;
	}
	while (src[i] && i + j + 1 < dstsize)
		*dst++ = src[i++];
	if (dstsize && j <= dstsize)
		*dst = '\0';
	while (src[i])
		i++;
	return ((j <= dstsize) ? i + j : dstsize + i);
}
