/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:32:38 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/03 15:32:41 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	size_t	l;
	size_t	r;
	size_t	i;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	l = 0;
	r = ft_strlen(s);
	i = 0;
	while (s[l] == ' ' || s[l] == '\n' || s[l] == '\t')
		l++;
	while (r > 0 && (s[r - 1] == ' ' || s[r - 1] == '\n' || s[r - 1] == '\t'))
		r--;
	if (l > r)
		r = l;
	ptr = (char*)malloc(r - l + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[r - l] = '\0';
	while (l < r--)
		ptr[r - l] = s[r];
	return (ptr);
}
