/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 12:36:41 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/29 12:36:43 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*s1copy;

	s1copy = s1;
	i = 0;
	while (*s1copy)
		s1copy++;
	while (s2[i] && i < n)
		*s1copy++ = s2[i++];
	*s1copy = '\0';
	return (s1);
}
