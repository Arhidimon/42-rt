/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:31:03 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/26 18:31:25 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if ((char *)dst <= (char *)src)
		while (i++ < len)
			*((char *)(dst + i - 1)) = (*(char *)(src + i - 1));
	else
	{
		i = len;
		while (i-- > 0)
			*((char *)(dst + i)) = (*(char *)(src + i));
	}
	return (dst);
}
