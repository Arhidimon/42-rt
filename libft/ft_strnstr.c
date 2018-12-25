/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:11:51 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/29 14:11:53 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*str;
	char	*to_find;

	str = (char*)haystack;
	to_find = (char*)needle;
	i = 0;
	if (*to_find == '\0')
		return (str);
	while (*str && len > 0)
	{
		while (*(str + i) == *(to_find + i) && *(to_find + i) && len > i)
			i++;
		if (*(to_find + i) == '\0')
			return (str);
		else
			i = 0;
		str++;
		len--;
	}
	return (NULL);
}
