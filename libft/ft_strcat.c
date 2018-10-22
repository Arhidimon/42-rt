/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 12:35:53 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/29 12:35:56 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	char	*s1copy;

	s1copy = s1;
	i = 0;
	while (*s1copy)
		s1copy++;
	while (s2[i])
		*s1copy++ = s2[i++];
	*s1copy = '\0';
	return (s1);
}
