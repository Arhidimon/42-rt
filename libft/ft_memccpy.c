/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:38:24 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/25 19:38:24 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)(dst + i)) = (*(unsigned char *)(src + i));
		if ((*(unsigned char *)(src + i)) == (unsigned char)c)
			return (((void*)((unsigned char *)(dst + i + 1))));
		i++;
	}
	return (NULL);
}
