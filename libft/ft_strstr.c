/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:07:02 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/29 14:07:08 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	char	*str;
	char	*to_find;

	str = (char*)haystack;
	to_find = (char*)needle;
	i = 0;
	if (*to_find == '\0')
		return (str);
	while (*str)
	{
		while (*(str + i) == *(to_find + i) && *(to_find + i))
			i++;
		if (*(to_find + i) == '\0')
			return (str);
		else
			i = 0;
		str++;
	}
	return (NULL);
}
