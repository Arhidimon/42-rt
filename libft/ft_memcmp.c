/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:00:08 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/26 20:00:17 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && *((unsigned char*)s1 + i) == *((unsigned char*)s2 + i))
		i++;
	if (i == n)
		return (0);
	else
		return (*((unsigned char*)s1 + i) - *((unsigned char*)s2 + i));
}
